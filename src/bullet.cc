#include "bullet.h"
#include "global.h"

const size_t bullet_width = UNITS_PER_PIXEL * 1;
const std::chrono::high_resolution_clock::duration lifespan(std::chrono::seconds(1));

Bullet::Bullet(const Position &ip, const Velocity &iv) :
    Object(ip, iv)
{
    _spawn_time = std::chrono::high_resolution_clock::now();
}

std::string Bullet::str() const{
    return "Bullet";
}

Bounding_Box Bullet::bounding_box() const{
    return Bounding_Box(_position, bullet_width);
}

std::chrono::high_resolution_clock::duration Bullet::ttl(const std::chrono::high_resolution_clock::time_point &now) const{
    if( (_spawn_time + lifespan) > now ){
        return std::chrono::seconds(0);
    }
    else{
        return (now - _spawn_time);
    }
}
