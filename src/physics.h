#ifndef __PHYSICS_H__
#define __PHYSICS_H__

//All physics calculations are done in a large but finite square 2^64 x 2^64
//Positions of Objects are squashed into pixel values as a last step before
//rendering by dividing x and y coordinates by a constant factor to scale down
//to screen resolution.

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
