#pragma once

#include "Ambient.hpp"
#include "../Samplers/Sampler.hpp"

class AmbientOccluder : public Ambient {
public:
    AmbientOccluder();
    AmbientOccluder(const AmbientOccluder& amb);
    AmbientOccluder& operator=(const AmbientOccluder& rhs);
    AmbientOccluder* clone() const;
    
    void set_sampler(Sampler* s_ptr);
    void set_min_amount(RGBColor min);
    void set_min_amount(float a);
    void set_min_amount(float r, float g, float b);
    
    virtual Vector3D get_direction(ShadeRec& sr);
    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
    virtual RGBColor L(ShadeRec& sr);

private:
    Vector3D u, v, w;
    Sampler* sampler_ptr;
    RGBColor min_amount;
};