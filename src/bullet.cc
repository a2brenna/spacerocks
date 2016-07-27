#include "bullet.h"
#include "global.h"

const size_t bullet_width = UNITS_PER_PIXEL * 1;
const std::chrono::high_resolution_clock::duration lifespan(std::chrono::seconds(3));

Bullet::Bullet(const Position &ip, const Velocity &iv, const std::chrono::high_resolution_clock::time_point &now) :
    Object(ip, iv)
{
    _spawn_time = now;
}

std::string Bullet::str() const{
    return "Bullet";
}

Bounding_Box Bullet::bounding_box() const{
    return Bounding_Box(_position, bullet_width);
}

std::chrono::high_resolution_clock::duration Bullet::ttl(const std::chrono::high_resolution_clock::time_point &now) const{
    return (_spawn_time + lifespan) - now;
}
