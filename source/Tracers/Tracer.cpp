#include "Tracer.hpp"

Tracer::Tracer()
	: world_ptr(NULL)
{}

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}

Tracer::~Tracer() {
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor Tracer::trace_ray(const Ray& ray) const {
	return (black);
}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
	return (black);
}


RGBColor Tracer::trace_ray(const Ray ray, float& tmin, const int depth) const {
	return (black);
}

void Tracer::set_world_ptr(World* world_ptr_){
	world_ptr = world_ptr_;
}

World* Tracer::get_world_ptr() const{
	return world_ptr;
}