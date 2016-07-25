#include "ship.h"
#include "global.h"

const size_t ship_width = UNITS_PER_PIXEL * 10;

std::string Ship::str() const{
    return "Ship";
}

Bounding_Box Ship::bounding_box() const{
    return Bounding_Box(_position, ship_width);
}
