#include "Material.hpp"

Material::Material()
{}

Material::Material(Material& material)
{}

Material::~Material()
{}

RGBColor Material::shade(ShadeRec& sr){
    return RGBColor(0);
}

RGBColor Material::area_light_shade(ShadeRec& sr){
    return RGBColor(0);
}

RGBColor Material::path_shade(ShadeRec& sr){
    return RGBColor(0);
}