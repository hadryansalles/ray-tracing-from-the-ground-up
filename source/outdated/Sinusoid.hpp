#pragma once

#include "Tracer.hpp"
#include <math.h>

class Sinusoid : public Tracer{
public:  
    Sinusoid(){ }
    Sinusoid(World* _world_ptr){ world_ptr = _world_ptr; }
    ~Sinusoid(){ world_ptr = NULL; }
    
    virtual RGBColor trace_ray(const Ray& ray) const {
        return RGBColor(0.5 * (1 + sin(pow(ray.o.x, 2)*pow(ray.o.y, 2))));
    }
};