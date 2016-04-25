#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
#include <chrono>

size_t FRAMES_RENDERED = 0;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

size_t CONFIG_SCREEN_WIDTH = 800;
size_t CONFIG_SCREEN_HEIGHT = 600;
bool CONFIG_VSYNC = false;
const uint64_t ten_seconds_in_nanos = 10 * 1000000000;
uint64_t max_start_velocity = std::numeric_limits<uint64_t>::max() / ten_seconds_in_nanos;
uint64_t min_start_velocity = max_start_velocity / 5;

#include "space.h"
Space space;

#include "rock.h"

#include <random>

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

void populate_universe(Space &space){
    std::default_random_engine re;
    std::uniform_int_distribution<uint64_t> rand_p_component;
    std::uniform_int_distribution<int64_t> rand_v_component(min_start_velocity, max_start_velocity);

    for(int i = 0; i < 10; i++){
        const Position initial_p(rand_p_component(re), rand_p_component(re));
        const Velocity initial_v(rand_v_component(re), rand_v_component(re));
        std::cerr << "Add: Rock: " << initial_p << " " << initial_v << std::endl;
        space.add_object(std::shared_ptr<Object>(new Rock(initial_p, initial_v)));
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

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

    populate_universe(space);

    const auto start_time = std::chrono::high_resolution_clock::now();
    bool running = true;

    auto universe_time = start_time;
    while(running){

        SDL_Event e;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                running = false;
                break;
            }
        }
        if(!running){
            break;
        }

        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto interval = current_time - universe_time;
        space.step(interval);
        std::cerr << space << std::endl;

        SDL_RenderClear( renderer );
        SDL_RenderPresent( renderer );
        FRAMES_RENDERED++;

        universe_time = current_time;
    }
    const auto end_time = std::chrono::high_resolution_clock::now();

    std::cerr << "FPS: " << FRAMES_RENDERED / std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << std::endl;

    return 0;
}
