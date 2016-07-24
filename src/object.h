#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "physics.h"
#include <chrono>
#include <iostream>

//This superclass defines the mininimum information required to track an object
//in the game
class Bounding_Box {

    private:
        uint64_t _max_x;
        uint64_t _min_x;
        uint64_t _max_y;
        uint64_t _min_y;

    public:
        Bounding_Box(const uint64_t &min_x, const uint64_t &min_y, const uint64_t &max_x, const uint64_t &max_y);
        uint64_t max_x() const;
        uint64_t min_x() const;
        uint64_t max_y() const;
        uint64_t min_y() const;

};

bool intersecting(const Bounding_Box &a, const Bounding_Box &b);

class Object {

    public:

        Object(const Position &initial_placement, const Velocity &initial_velocity);
        Position _position;
        Position position() const;
        Velocity _velocity;
        Velocity velocity() const;
        void step(const std::chrono::high_resolution_clock::duration &t);

        //virtual Bounding_Box bounding_box() const = 0;

        virtual std::string str() const = 0;

};

std::ostream &operator<<(std::ostream& os, const Object &o);

#endif
