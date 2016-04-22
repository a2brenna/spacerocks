#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "physics.h"

//This superclass defines the mininimum information required to track an object
//in the game
class Object {

    public:

        Object(const Position &initial_placement);
        Position _position;

};


#endif
