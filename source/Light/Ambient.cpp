#include "Ambient.hpp"

Ambient::Ambient(float ls_, RGBColor color_, bool shadows_):
    Light(shadows_),
    ls(ls_),
    color(color_)
{}

Ambient::Ambient(const Ambient& ambient):
    Light(ambient.get_shadows()),
    ls(ambient.get_ls()),
    color(ambient.get_color())    
{}

Light* Ambient::clone() const {
	return (new Ambient(*this));
}	

Ambient& Ambient::operator= (const Ambient& rhs) {
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}

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