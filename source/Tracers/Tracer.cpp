#include "Tracer.hpp"
#include "../World/World.hpp"

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