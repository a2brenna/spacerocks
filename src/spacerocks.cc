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

    //SDL_Texture *texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT );
    //assert(texture);

    const auto start_time = std::chrono::high_resolution_clock::now();
    bool running = true;
    while(running){

        SDL_Event e;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_RenderClear( renderer );
        SDL_RenderPresent( renderer );
        //SDL_RenderCopy( renderer, texture, NULL, NULL);
        FRAMES_RENDERED++;
    }
    const auto end_time = std::chrono::high_resolution_clock::now();

    std::cerr << "FPS: " << FRAMES_RENDERED / std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << std::endl;

    return 0;
}
