#pragma once

#include "BRDF.hpp"

class GlossySpecular : public BRDF{
public:
    GlossySpecular(float kd_ = 0.0, float exp_ = 0.0, RGBColor cd_ = RGBColor(0));
    GlossySpecular(const GlossySpecular& lamb);
    virtual GlossySpecular* clone() const;
    GlossySpecular& operator=(const GlossySpecular& rhs);

    float get_kd() const;
    void set_kd(const float kd);

    float get_exp() const;
    void set_exp(const float exp_);

    RGBColor get_cd() const;
    void set_cd(const RGBColor cd);

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    float kd;
    float E;
    RGBColor cd;
};