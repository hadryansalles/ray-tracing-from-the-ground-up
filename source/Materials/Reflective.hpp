#pragma once

#include "Phong.hpp"
#include "../BRDF/PerfectSpecular.hpp"

class Reflective : public Phong {
public:
    Reflective();
    Reflective(const Reflective& refl);
    virtual Reflective* clone() const;
    virtual Reflective* clone(RGBColor new_color) const;
    Reflective& operator=(const Reflective& rhs);

    void set_kr(const float k);
    void set_cr(const RGBColor c);
    void set_cr(const float r, const float g, const float b);
    void set_cr(const float a); 
    
    virtual RGBColor shade(ShadeRec& sr);

private:
    PerfectSpecular* reflective_brdf;
};