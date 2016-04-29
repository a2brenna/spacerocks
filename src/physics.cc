#include "physics.h"

Velocity::Velocity(const int64_t &initial_x, const int64_t &initial_y, const int64_t &initial_r){
    x = initial_x;
    y = initial_y;
    r = initial_r;
}

Position::Position(const uint64_t &initial_x, const uint64_t &initial_y, const uint64_t &initial_r){
    x = initial_x;
    y = initial_y;
    r = initial_r;
}

Displacement::Displacement(const Velocity &v, const std::chrono::high_resolution_clock::duration &t){
    x = v.x * t.count();
    y = v.y * t.count();
    r = v.r * t.count();
}

Velocity operator+(const Velocity &a, const Velocity &b){
    return Velocity(a.x + b.x, a.y + b.y, a.r + b.r);
}

Position operator+(const Position &a, const Displacement &b){
    return Position(a.x + b.x, a.y + b.y, a.r + b.r);
}

std::ostream &operator<<(std::ostream& os, const Velocity &v){
    return os << "(" << v.x << ", " << v.y << ")";
}

std::ostream &operator<<(std::ostream& os, const Position &p){
    return os << "(" << p.x << ", " << p.y << ")";
}
