#include "rock.h"
#include "global.h"

const size_t rock_width = UNITS_PER_PIXEL * 10;

std::string Rock::str() const{
    return "Rock";
}

Bounding_Box Rock::bounding_box() const{
    return Bounding_Box(_position, rock_width);
}
