#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <memory>
#include <chrono>

#include "object.h"

class Space{

    private:

        std::vector<std::shared_ptr<Object>> _objects;

    public:

        void step(const std::chrono::high_resolution_clock::duration &interval);
        void add_object(std::shared_ptr<Object> new_object);
        const std::vector<std::shared_ptr<Object>> objects() const;
        std::string str() const;

};

std::ostream &operator<<(std::ostream &o, const Space &s);

#endif
