#ifndef __BULLET_H__
#define __BULLET_H__

#include "object.h"

class Bullet: public Object{

    public:
        using Object::Object;
        std::string str() const;
        Bounding_Box bounding_box() const;

};

#endif
