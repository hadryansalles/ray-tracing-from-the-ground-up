#include "Light.hpp"

Light::Light(const bool shadows_):
    shadows(shadows_)
{}

Light::Light(Light& light):
    shadows(light.get_shadows())
{}

Light::~Light()
{}

bool Light::get_shadows() const{
    return shadows;
}

void Light::set_shadows(const bool shadows_){
    shadows = shadows_;
}