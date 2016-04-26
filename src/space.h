#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <memory>
#include <chrono>

#include "object.h"
#include "rock.h"
#include "ship.h"

class Space{

    private:

        std::vector<std::shared_ptr<Rock>> _rocks;
        std::shared_ptr<Ship> _ship;

    public:

        void step(const std::chrono::high_resolution_clock::duration &interval);
        void add_rock(std::shared_ptr<Rock> new_rock);
        const std::vector<std::shared_ptr<Rock>> rocks() const;
        std::string str() const;

};

std::ostream &operator<<(std::ostream &o, const Space &s);

#endif
