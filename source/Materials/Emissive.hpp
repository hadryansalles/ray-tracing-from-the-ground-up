#pragma once

#include "Material.hpp"

class Emissive : public Material {
private:
    float ls;
    RGBColor ce;

public:
    Emissive(const float ls_ = 1, const RGBColor ce_ = RGBColor(1));
    Emissive(const Emissive& emissive);
    Emissive& operator=(const Emissive& rhs);
    Emissive* clone() const;

    void scale_radiance(const float ls_);
    void set_ce(const float r, const float g, const float b);
    void set_ce(const float a);
    void set_ce(const RGBColor ce_);

    virtual RGBColor get_Le(ShadeRec& sr) const;
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
};