#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <memory>
#include <chrono>

#include "object.h"

class Space{

    private:

        std::vector<Object> _objects;

    public:

        void step(const std::chrono::high_resolution_clock::duration &interval);

};

#endif
