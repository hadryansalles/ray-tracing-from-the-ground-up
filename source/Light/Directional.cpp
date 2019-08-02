#include "Directional.hpp"

Directional::Directional(Vector3D dir_, const float ls_, const RGBColor color_, bool shadows_):
    Ambient(ls_, color_, shadows_),
    dir(dir_)
{}

Directional::Directional(const Directional& dl):
    Ambient(dl),
    dir(dl.dir)
{}

Light* Directional::clone() const {
    return (new Directional(*this));
}

Directional& Directional::operator=(const Directional& rhs){
    if(this == &rhs){
        return (*this);
    }
    Ambient::operator=(rhs);
    dir = rhs.dir;
    return (*this);
}

void Directional::set_direction(Vector3D d){
    dir = d;
}

Vector3D Directional::get_direction(ShadeRec& sr){
    return dir;
}

RGBColor Directional::L(ShadeRec& sr){
    return (ls * color);
}
