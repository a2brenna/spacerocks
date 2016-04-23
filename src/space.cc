#include "space.h"

void Space::step(const std::chrono::high_resolution_clock::duration &interval){

    //move _objects to new posiitions
    for(auto &o: _objects){
        o->step(interval);
    }

    //check for collisions

}
