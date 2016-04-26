#include "space.h"
#include <sstream>

void Space::step(const std::chrono::high_resolution_clock::duration &interval){

    //move _rocks to new posiitions
    for(auto &o: _rocks){
        o->step(interval);
    }

    //check for collisions

}

void Space::add_rock(std::shared_ptr<Rock> new_rock){
    _rocks.push_back(new_rock);
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

std::ostream &operator<<(std::ostream &o, const Space &s){
    return o << s.str();
}
