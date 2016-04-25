#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "physics.h"
#include <chrono>
#include <iostream>

//This superclass defines the mininimum information required to track an object
//in the game
class Object {

    public:

        Object(const Position &initial_placement, const Velocity &initial_velocity);
        Position _position;
        Velocity _velocity;
        void step(const std::chrono::high_resolution_clock::duration &t);

        virtual std::string str() const = 0;

};

std::ostream &operator<<(std::ostream& os, const Object &o);

#endif
