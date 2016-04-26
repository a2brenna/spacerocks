#ifndef __SHIP_H__
#define __SHIP_H__

#include "object.h"

class Ship : public Object{

    public:
        using Object::Object;
        std::string str() const;

};

#endif
