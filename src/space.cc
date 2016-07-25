#include "space.h"
#include <sstream>

std::shared_ptr<Ship> Space::ship(){
    return _ship;
}

void Space::step(const std::chrono::high_resolution_clock::duration &interval){

    //move _bullets to new positions
    for(auto &o: _bullets){
        o->step(interval);
    }

    //move _rocks to new posiitions
    for(auto &o: _rocks){
        o->step(interval);
    }
    _ship->step(interval);

    //check for collisions

}

void Space::add_rock(std::shared_ptr<Rock> new_rock){
    _rocks.push_back(new_rock);
}

void Space::add_bullet(std::shared_ptr<Bullet> new_bullet){
    _bullets.insert(new_bullet);
}

void Space::place_ship(std::shared_ptr<Ship> new_ship){
    _ship = new_ship;
}

std::string Space::str() const{
    std::stringstream out;
    out << "Space";

    if(_rocks.empty()){
        return out.str();
    }
    else{
        out << std::endl;
        out << *(_rocks[0]);
        for(size_t i = 1; i < _rocks.size(); i++){
            out << std::endl;
            out << *(_rocks[i]);
        }
        return out.str();
    }
}

const std::vector<std::shared_ptr<Rock>> Space::rocks() const{
    return _rocks;
}

const std::set<std::shared_ptr<Bullet>> Space::bullets() const{
    return _bullets;
}

const std::shared_ptr<Ship> Space::ship() const{
    return _ship;
}

const std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> Space::collisions() const{
    std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> colliding_objects;

    for(const auto &r: _rocks){
        if(intersecting(_ship->bounding_box(), r->bounding_box())){
            colliding_objects.push_back(std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>(_ship, r));
        }
    }
    return colliding_objects;
}

std::ostream &operator<<(std::ostream &o, const Space &s){
    return o << s.str();
}
