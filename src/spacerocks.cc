#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>

size_t SCREEN_WIDTH = 800;
size_t SCREEN_HEIGHT = 600;


int main(int argc, char *argv[]){
    std::cout << "Starting Spacerocks..." << std::endl;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cerr << "Fatal SDL_Init(...) error" << std::endl;
        return -1;
    }

    SDL_Window *window(SDL_CreateWindow( "Spacerocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ));
    assert(window);

    bool running = true;
    while(running){

        SDL_Event e;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_UpdateWindowSurface(window);
        SDL_Delay(20);
    }

    return 0;
}
