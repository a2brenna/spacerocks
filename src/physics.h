#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdint.h>

class Position {

    public:

        uint64_t x;
        uint64_t y;

};

class Displacement {

    public:

        int64_t x;
        int64_t y;

};

class Velocity {

    public:

        int64_t x;
        int64_t y;

};

#endif
