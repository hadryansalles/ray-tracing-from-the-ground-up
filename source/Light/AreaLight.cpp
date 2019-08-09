#include "AreaLight.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../World/World.hpp"

AreaLight::AreaLight(void)
	: 	Light(),
		object_ptr(NULL),
		material_ptr(NULL)
{}	
	
AreaLight::AreaLight(const AreaLight& alight)
	: 	Light(alight) {
	if(alight.object_ptr)
		object_ptr = alight.object_ptr->clone(); 
	else  object_ptr = NULL;
	
	if(alight.material_ptr)
		material_ptr = alight.material_ptr->clone(); 
	else  material_ptr = NULL;
}

AreaLight* AreaLight::clone() const {
	return (new AreaLight(*this));
}					
					
AreaLight::~AreaLight(void) {

}

AreaLight& AreaLight::operator= (const AreaLight& rhs) {
	if (this == &rhs)
		return (*this);
		
	Light::operator=(rhs);
	
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
		
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}

Vector3D AreaLight::get_direction(ShadeRec& sr) {
	sample_point = object_ptr->sample();    // used in the G function
	light_normal = object_ptr->get_normal(sample_point); 
	wi = sample_point - sr.hit_point;  		// used in the G function
	wi.normalize();
	
	return (wi);
}

RGBColor AreaLight::L(ShadeRec& sr) {
	float ndotd = -light_normal * wi; 
	
	if (ndotd > 0.0)		
		return (material_ptr->get_Le(sr)); 
	else
		return (black);
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	float ts = (sample_point - ray.o) * ray.d;
	
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
			return (true); 
		
	return (false);     
}

float AreaLight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sr.hit_point);
		
	return (ndotd / d2);
}

float AreaLight::pdf(const ShadeRec& sr) const {
	return (object_ptr->pdf(sr));
}


void AreaLight::set_object(GeometricObject* object) {
	object_ptr = object;
	if(object_ptr){
		material_ptr = object_ptr->get_material();
	}
}