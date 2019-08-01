#include "PointLight.hpp"

PointLight::PointLight(Vector3D location_, float ls_, RGBColor color_, bool shadows_):
    Ambient(ls_, color_, shadows_),
    location(location_)
{}

PointLight::PointLight(PointLight& point):
    Ambient(point),
    location(point.get_location())
{}

Vector3D PointLight::get_location() const{
    return location;
}

void PointLight::set_location(const Vector3D location_){
    location = location_;
}

Vector3D PointLight::get_direction(ShadeRec& sr){
    return ((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr){
    return (ls * color);
}