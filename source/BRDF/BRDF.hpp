#pragma once

#include "../Samplers/Sampler.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/ShadeRec.hpp"

class BRDF{
public:
    BRDF();
    BRDF(const BRDF& brdf);
    BRDF(Sampler* sampler);
    BRDF& operator=(const BRDF& rhs);
    virtual BRDF* clone() const = 0;

    virtual ~BRDF();

    void set_sampler(Sampler* sampler);
    Sampler* get_sampler() const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wi, float& pdf) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    Sampler* sampler_ptr;
};