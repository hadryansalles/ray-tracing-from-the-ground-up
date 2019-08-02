#pragma once

#include "BRDF.hpp"

class Lambertian : public BRDF{
public:
    Lambertian(float kd_ = 0, RGBColor cd_ = RGBColor(1));
    Lambertian(const Lambertian& lamb);
    virtual Lambertian* clone() const;
    Lambertian& operator=(const Lambertian& rhs);

    float get_kd() const;
    void set_kd(const float kd);

    RGBColor get_cd() const;
    void set_cd(const RGBColor cd);

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    float kd;
    RGBColor cd;
};