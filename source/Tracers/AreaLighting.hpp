#pragma once

#include "Tracer.hpp"

class AreaLighting : public Tracer {
public:
    AreaLighting(World* world_ptr_ = NULL);

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;
};