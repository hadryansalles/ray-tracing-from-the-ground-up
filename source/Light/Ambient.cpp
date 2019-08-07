#include "Ambient.hpp"

Ambient::Ambient ()
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}

Ambient::Ambient (const Ambient& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
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

Ambient::~Ambient () {}

Vector3D Ambient::get_direction(ShadeRec& s) {
	return (Vector3D(0.0));
}

RGBColor Ambient::L(ShadeRec& sr) {	
    return (ls * color);
}

void Ambient::scale_radiance(const float b) { 
	ls = b;
}

void Ambient::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}

void Ambient::set_color(const RGBColor& c) {
	color = c;
}

void Ambient::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

bool Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	return false;
}
