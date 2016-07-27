#ifndef __BULLET_H__
#define __BULLET_H__

#include "object.h"

class Bullet: public Object{

    public:
        Bullet(const Position &initial_placement, const Velocity &initial_velocity);
        std::string str() const;
        Bounding_Box bounding_box() const;

        std::chrono::high_resolution_clock::duration ttl(const std::chrono::high_resolution_clock::time_point &now) const;

    private:
        std::chrono::high_resolution_clock::time_point _spawn_time;

};

#endif
