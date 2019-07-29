#pragma once

#include "Tracer.hpp"
#include "../World/World.hpp"
#include "../Utilities/ShadeRec.hpp"

class SingleSphere: public Tracer {
public:	
	SingleSphere();									
	SingleSphere(World* _worldPtr);					

	virtual ~SingleSphere();
	virtual RGBColor trace_ray(const Ray& ray) const;
};