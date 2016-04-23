#include "object.h"

Object::Object(const Position &initial_placement, const Velocity &initial_velocity) :
    _position(initial_placement),
    _velocity(initial_velocity)
{
}

void Object::step(const std::chrono::high_resolution_clock::duration &interval){

}
