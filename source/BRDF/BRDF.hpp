#pragma once

#include "../Samplers/Sampler.hpp"
#include "../Utilities/ShadeRec.hpp"

class BRDF{
public:
    BRDF();
    BRDF(Sampler* sampler);
    virtual ~BRDF();

    void set_sampler(Sampler* sampler);
    Sampler* get_sampler() const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const = 0;
    virtual RGBColor rho(ShadeRec& sr, const Vector3D& wo) const = 0;

protected:
    Sampler* sampler_ptr;
};