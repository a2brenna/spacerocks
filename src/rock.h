#ifndef __ROCK_H__
#define __ROCK_H__

#include "object.h"

class Rock : public Object{

    public:
        using Object::Object;
        std::string str() const;
        Bounding_Box bounding_box() const;

};

#endif
