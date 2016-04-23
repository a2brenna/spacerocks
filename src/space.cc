#include "space.h"

void Space::update(const std::chrono::high_resolution_clock::time_point &new_time){
    const auto _dtime = new_time - _current_time;

    //move _objects to new posiitions
    //check for collisions

    _current_time = new_time;
}
