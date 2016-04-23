#include "space.h"

void Space::step(const std::chrono::high_resolution_clock::duration &interval){

    //move _objects to new posiitions
    for(auto &o: _objects){
        o->step(interval);
    }

    //check for collisions

}

void Space::add_object(std::shared_ptr<Object> new_object){
    _objects.push_back(new_object);
}
