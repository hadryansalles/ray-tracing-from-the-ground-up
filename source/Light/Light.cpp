#include "Light.hpp"

Light::Light(const bool shadows_):
    shadows(shadows_)
{}

Light::Light(const Light& light):
    shadows(light.get_shadows())
{}

Light& Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

Light::~Light()
{}

bool Light::get_shadows() const{
    return shadows;
}

void Light::set_shadows(const bool shadows_){
    shadows = shadows_;
}

bool Light::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    return false;
}
