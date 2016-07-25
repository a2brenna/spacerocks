#include "bullet.h"
#include "global.h"

const size_t bullet_width = UNITS_PER_PIXEL * 1;

std::string Bullet::str() const{
    return "BUllet";
}

Bounding_Box Bullet::bounding_box() const{
    return Bounding_Box(_position, bullet_width);
}
