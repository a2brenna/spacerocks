#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <memory>
#include <chrono>

#include "object.h"

class Space{

    private:

        std::chrono::high_resolution_clock::time_point _current_time;
        std::vector<Object> _objects;

    public:

        void update(const std::chrono::high_resolution_clock::time_point &new_time);

};

#endif
