#include "space.h"
#include <sstream>

void Space::step(const std::chrono::high_resolution_clock::duration &interval){

    //move _objects to new posiitions
    for(auto &o: _objects){
        o->step(interval);
    }

    //check for collisions

}

void Space::add_object(std::shared_ptr<Object> new_object){
    _objects.push_back(new_object);
}

std::string Space::str() const{
    std::stringstream out;
    out << "Space";

    if(_objects.empty()){
        return out.str();
    }
    else{
        out << std::endl;
        out << *(_objects[0]);
        for(size_t i = 1; i < _objects.size(); i++){
            out << std::endl;
            out << *(_objects[i]);
        }
        return out.str();
    }
}

const std::vector<std::shared_ptr<Object>> Space::objects() const{
    return _objects;
}

std::ostream &operator<<(std::ostream &o, const Space &s){
    return o << s.str();
}
