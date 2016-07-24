#include "object.h"
#include <cassert>

Object::Object(const Position &initial_placement, const Velocity &initial_velocity) :
    _position(initial_placement),
    _velocity(initial_velocity)
{
}

void Object::step(const std::chrono::high_resolution_clock::duration &interval){
    const Displacement displacement(_velocity, interval);
    _position = _position + displacement;
}

Position Object::position() const{
    return _position;
}

Velocity Object::velocity() const{
    return _velocity;
}

std::ostream &operator<<(std::ostream &os, const Object &o){
    return os << o.str() << " " << o._position << " " << o._velocity;
}

Bounding_Box::Bounding_Box(const uint64_t &min_x, const uint64_t &min_y, const uint64_t &max_x, const uint64_t &max_y){
    assert(min_x < max_x);
    assert(min_y < max_y);
    _min_x = min_x;
    _max_x = max_x;
    _min_y = min_y;
    _max_y = max_y;
}

uint64_t Bounding_Box::min_x() const{
    return _min_x;
}

uint64_t Bounding_Box::max_x() const{
    return _max_x;

}

uint64_t Bounding_Box::min_y() const{
    return _min_y;

}

uint64_t Bounding_Box::max_y() const{
    return _max_y;
}

bool intersecting(const Bounding_Box &a, const Bounding_Box &b){
    const bool x_intersect = (b.min_x() >= a.min_x() && b.min_x() <= a.max_x()) || (a.min_x() >= b.min_x() && a.min_x() <= b.max_x());
    const bool y_intersect = (b.min_x() >= a.min_x() && b.min_x() <= a.max_x()) || (a.min_x() >= b.min_x() && a.min_x() <= b.max_x());
    return x_intersect && y_intersect;
}
