#pragma once

#include "../Utilities/RGBColor.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Samplers/Sampler.hpp"

class BTDF{
public:
    BTDF();
    BTDF(const BTDF& btdf);
    BTDF(Sampler* sampler);
    BTDF& operator=(const BTDF& rhs);
    virtual BTDF* clone() const = 0;
    virtual ~BTDF();

    void set_sampler(Sampler* sampler);
    Sampler* get_sampler() const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const = 0;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt) const = 0;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt, float& pdf) const = 0;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const = 0;
    virtual bool tir(const ShadeRec& sr) const = 0;

private:
    Sampler* sampler_ptr;
};