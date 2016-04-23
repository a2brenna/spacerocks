#include "physics.h"

Velocity::Velocity(const int64_t &initial_x, const int64_t &initial_y){
    x = initial_x;
    y = initial_y;
}

Position::Position(const uint64_t &initial_x, const uint64_t &initial_y){
    x = initial_x;
    y = initial_y;
}

Displacement::Displacement(const Velocity &v, const std::chrono::high_resolution_clock::duration &t){
    x = v.x * t.count();
    y = v.y * t.count();
}

Velocity operator+(const Velocity &a, const Velocity &b){
    return Velocity(a.x + b.x, a.y + b.y);
}

Position operator+(const Position &a, const Displacement &b){
    return Position(a.x + b.x, a.y + b.y);
}
