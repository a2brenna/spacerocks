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

Bounding_Box::Bounding_Box(const Position &p, const size_t &width){
    if( p.x >= width){
        _min_x = p.x - width;
    }
    else{
        _min_x = 0;
    }

    if( p.y >= width){
        _min_y = p.y - width;
    }
    else{
        _min_y = 0;
    }

    if( (std::numeric_limits<uint64_t>::max() - width) >= p.x){
        _max_x = p.x + width;
    }
    else{
        _max_x = std::numeric_limits<uint64_t>::max();
    }

    if( (std::numeric_limits<uint64_t>::max() - width) >= p.y){
        _max_y = p.y + width;
    }
    else{
        _max_y = std::numeric_limits<uint64_t>::max();
    }
    assert(_min_x <= _max_x);
    assert(_min_y <= _max_y);
}

Bounding_Box::Bounding_Box(const uint64_t &min_x, const uint64_t &min_y, const uint64_t &max_x, const uint64_t &max_y){
    assert(min_x <= max_x);
    assert(min_y <= max_y);
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
    const bool y_intersect = (b.min_y() >= a.min_y() && b.min_y() <= a.max_y()) || (a.min_x() >= b.min_y() && a.min_y() <= b.max_y());
    return x_intersect && y_intersect;
}

std::ostream &operator<<(std::ostream &os, const Bounding_Box &b){
    return os << "Bounding_Box: (" << b.min_x() << "," << b.min_y() << ") (" << b.max_x() << "," << b.max_y() << ")";
}

