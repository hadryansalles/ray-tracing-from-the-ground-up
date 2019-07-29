#pragma once

// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#include "../Utilities/Constants.hpp"
#include "../Utilities/Ray.hpp"
#include "../Utilities/RGBColor.hpp"

class World;

class Tracer {
public:
	Tracer();									
	Tracer(World* _world_ptr);						
	virtual ~Tracer();									

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
			
protected:
	World* world_ptr;
};