#pragma once

#include "BRDF.hpp"

class PerfectSpecular : public BRDF{
public:
    PerfectSpecular(float kr_ = 0.0, RGBColor cr_ = RGBColor(0));
    PerfectSpecular(const PerfectSpecular& perf);
    virtual PerfectSpecular* clone() const;
    PerfectSpecular& operator=(const PerfectSpecular& rhs);

    float get_kr() const;
    void set_kr(const float kr);

    RGBColor get_cr() const;
    void set_cr(const RGBColor cr);

    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
  
protected:
    float kr;
    RGBColor cr;
};