#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <set>
#include <memory>
#include <chrono>

#include "object.h"
#include "rock.h"
#include "ship.h"
#include "bullet.h"

class Space{

    private:

        std::vector<std::shared_ptr<Rock>> _rocks;
        std::set<std::shared_ptr<Bullet>> _bullets;
        std::shared_ptr<Ship> _ship;

    public:

        void step(const std::chrono::high_resolution_clock::duration &interval);
        void add_rock(std::shared_ptr<Rock> new_rock);
        void add_bullet(std::shared_ptr<Bullet> new_bullet);
        void place_ship(std::shared_ptr<Ship> new_ship);
        std::shared_ptr<Ship> ship();

        const std::shared_ptr<Ship> ship() const;
        const std::vector<std::shared_ptr<Rock>> rocks() const;
        const std::set<std::shared_ptr<Bullet>> bullets() const;

        const std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> collisions() const;
        std::string str() const;

};

std::ostream &operator<<(std::ostream &o, const Space &s);

#endif
