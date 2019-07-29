#pragma once

#include "Tracer.hpp"
#include "../World/World.hpp"

class MultipleObjects: public Tracer {
public:
	MultipleObjects();							
	MultipleObjects(World* _world_ptr);				

	virtual ~MultipleObjects();
	virtual RGBColor trace_ray(const Ray& ray) const;
};