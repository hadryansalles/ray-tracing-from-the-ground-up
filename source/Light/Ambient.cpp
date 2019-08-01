#include "Ambient.hpp"

Ambient::Ambient(float ls_, RGBColor color_, bool shadows_):
    Light(shadows_),
    ls(ls_),
    color(color_)
{}

Ambient::Ambient(Ambient& ambient):
    Light(ambient.get_shadows()),
    ls(ambient.get_ls()),
    color(ambient.get_color())    
{}

float Ambient::get_ls() const{
    return ls;
}

void Ambient::set_ls(const float ls_){
    ls = ls_;
}

RGBColor Ambient::get_color() const{
    return color;
}

void Ambient::set_color(const RGBColor color_){
    color = color_;
}

Vector3D Ambient::get_direction(ShadeRec& sr){
    return (Vector3D(0.0));
}

RGBColor Ambient::L(ShadeRec& sr){
    return (ls*color);
}