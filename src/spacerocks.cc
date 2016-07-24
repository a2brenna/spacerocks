#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include <math.h>

size_t FRAMES_RENDERED = 0;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

size_t CONFIG_SCREEN_WIDTH = 800;
size_t CONFIG_SCREEN_HEIGHT = 800;
bool CONFIG_VSYNC = false;
const int64_t five_seconds_in_nanos = (int64_t)5 * (int64_t)1000000000;
int64_t max_start_velocity = std::numeric_limits<uint64_t>::max() / five_seconds_in_nanos;
int64_t min_start_velocity = -max_start_velocity;
int64_t max_start_rotation = std::numeric_limits<uint64_t>::max() / (int64_t)1000000000;
int64_t min_start_rotation = -max_start_rotation;

const int64_t THRUST = 100000000;

const double PI = 3.14159;

#include "space.h"
Space space;

#include "rock.h"
SDL_Texture *rock;
SDL_Texture *ship;

void get_config(int argc, char *argv[]){
    po::options_description desc("Options");
    desc.add_options()
        ("help", "Produce help message")
        ("x", po::value<size_t>(&CONFIG_SCREEN_WIDTH), "Screen width")
        ("y", po::value<size_t>(&CONFIG_SCREEN_HEIGHT), "Screen height")
        ("vsync", po::bool_switch(&CONFIG_VSYNC), "Enable vsync")
        ;

    po::variables_map vm;
    const auto cmdline_params = po::parse_command_line(argc, argv, desc);
    po::store(cmdline_params, vm);
    po::notify(vm);
}

#include <random>
void populate_universe(Space &space){
    std::default_random_engine re;
    std::uniform_int_distribution<uint64_t> rand_p_component;
    std::uniform_int_distribution<int64_t> rand_v_component(min_start_velocity, max_start_velocity);
    std::uniform_int_distribution<int64_t> rand_r_component(min_start_rotation, max_start_rotation);

    for(int i = 0; i < 10; i++){
        const Position initial_p(rand_p_component(re), rand_p_component(re), rand_p_component(re));
        const Velocity initial_v(rand_v_component(re), rand_v_component(re), rand_r_component(re));
        std::cerr << "Add: Rock: " << initial_p << " " << initial_v << std::endl;
        space.add_rock(std::shared_ptr<Rock>(new Rock(initial_p, initial_v)));
    }

    space.place_ship(std::shared_ptr<Ship>(new Ship(Position(std::numeric_limits<uint64_t>::max() / 2, std::numeric_limits<uint64_t>::max() / 2, 0), Velocity(0,0,0))));

}

std::pair<size_t, size_t> map_to_pixels(const Position &p){
    const uint64_t posn_pixel_ratio = std::numeric_limits<uint64_t>::max() / CONFIG_SCREEN_WIDTH;
    return std::pair<size_t, size_t>(p.x / posn_pixel_ratio, p.y / posn_pixel_ratio);
}

void render_space(SDL_Renderer *renderer, const Space &space, SDL_Texture *rock){
    for(const auto &o: space.rocks()){
        const auto pixel_posn = map_to_pixels(o->position());
        SDL_Rect renderQuad = { pixel_posn.first, pixel_posn.second, 20, 20 };
        const double rotation_degrees = ((double)o->position().r / std::numeric_limits<uint64_t>::max()) * 360;
        SDL_RenderCopyEx(renderer, rock, NULL, &renderQuad, rotation_degrees, NULL, SDL_FLIP_NONE);
    }

    {
        const auto pixel_posn = map_to_pixels(space.ship()->position());
        SDL_Rect renderQuad = { pixel_posn.first, pixel_posn.second, 20, 20 };
        const double rotation_degrees = ((double)space.ship()->position().r / std::numeric_limits<uint64_t>::max()) * 360;
        SDL_RenderCopyEx(renderer, ship, NULL, &renderQuad, rotation_degrees, NULL, SDL_FLIP_NONE);
    }

}

int main(int argc, char *argv[]){
    std::cout << "Starting Spacerocks..." << std::endl;

    get_config(argc, argv);

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cerr << "Fatal SDL_Init(...) error" << std::endl;
        return -1;
    }

    SDL_Window *window(SDL_CreateWindow( "Spacerocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, SDL_WINDOW_SHOWN ));
    assert(window);

    SDL_Renderer *renderer;
    if(CONFIG_VSYNC){
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    }
    else{
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    }
    assert(renderer);

	{
        SDL_Surface *temp = IMG_Load( "./rock.png" );
        rock = SDL_CreateTextureFromSurface( renderer, temp );
        SDL_FreeSurface(temp);
	}
    assert(rock);

	{
        SDL_Surface *temp = IMG_Load( "./ship.png" );
        ship = SDL_CreateTextureFromSurface( renderer, temp );
        SDL_FreeSurface(temp);
	}
    assert(ship);

    populate_universe(space);

    const auto start_time = std::chrono::high_resolution_clock::now();
    bool running = true;

    auto universe_time = start_time;
    while(running){

        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT){
            running = false;
            break;
        }
        const Uint8* current_key_states = SDL_GetKeyboardState( NULL );
        if( current_key_states[SDL_SCANCODE_UP] ){
            //adjust ship forward
            const auto r_rad = ( (double)(space.ship()->_position.r) / std::numeric_limits<uint64_t>::max()) * (2 * PI);
            const int64_t d_y = -1 * THRUST * cos(r_rad);
            const int64_t d_x = THRUST * sin(r_rad);
            const Velocity thrust(d_x, d_y, 0);
            space.ship()->_velocity = space.ship()->velocity() + thrust;
        }
        if( current_key_states[SDL_SCANCODE_LEFT] ){
            space.ship()->_position.r -= std::numeric_limits<uint64_t>::max() / 360 * 7;
        }
        if( current_key_states[SDL_SCANCODE_RIGHT] ){
            space.ship()->_position.r += std::numeric_limits<uint64_t>::max() / 360 * 7;
        }
        if( current_key_states[SDL_SCANCODE_SPACE] ){
            std::cerr << "PEW PEW" << std::endl;
            //fire gun
        }

        if(!running){
            break;
        }

        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto interval = current_time - universe_time;

        space.step(interval);

        for(const auto &c: space.collisions()){
            std::cerr << c.first << " " << c.second << " colliding" << std::endl;
        }

        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( renderer );
        render_space( renderer, space, rock );
        SDL_RenderPresent( renderer );
        FRAMES_RENDERED++;

        universe_time = current_time;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }
    const auto end_time = std::chrono::high_resolution_clock::now();

    std::cerr << "FPS: " << FRAMES_RENDERED / std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << std::endl;

    return 0;
}
