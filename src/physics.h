#ifndef __PHYSICS_H__
#define __PHYSICS_H__

//All physics calculations are done in a large but finite square 2^64 x 2^64
//Positions of Objects are squashed into pixel values as a last step before
//rendering by dividing x and y coordinates by a constant factor to scale down
//to screen resolution.

#include <stdint.h>
#include <chrono>
#include <iostream>

class Position {

    public:

        uint64_t x;
        uint64_t y;
        uint64_t r;
        Position(const uint64_t &initial_x, const uint64_t &initial_y, const uint64_t &initial_r);

};

class Velocity {

    public:

        int64_t x;
        int64_t y;
        int64_t r;
        Velocity(const int64_t &initial_x, const int64_t &initial_y, const int64_t &initial_r);

};

class Displacement {

    public:

        int64_t x;
        int64_t y;
        int64_t r;
        Displacement(const Velocity &v, const std::chrono::high_resolution_clock::duration &t);

};

Velocity operator+(const Velocity &a, const Velocity &b);
Position operator+(const Position &a, const Displacement &b);

std::ostream &operator<<(std::ostream& os, const Velocity &v);
std::ostream &operator<<(std::ostream& os, const Position &p);

#endif
