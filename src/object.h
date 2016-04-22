#ifndef __OBJECT_H__
#define __OBJECT_H__

//This superclass defines the mininimum information required to track an object
//in the game
class Object {

    public:

        Object(const int &initial_x, const int &initial_y);
        int x;
        int y;

};


#endif
