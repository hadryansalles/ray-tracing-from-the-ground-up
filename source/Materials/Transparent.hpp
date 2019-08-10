#pragma once

#include "../BRDF/PerfectSpecular.hpp"
#include "../BTDF/PerfectTransmitter.hpp"

#include "Phong.hpp"

class Transparent : public Phong {
public:
    Transparent();
    Transparent(const Transparent& rhs);
    Transparent& operator=(const Transparent& rhs);
    virtual Transparent* clone() const;
    ~Transparent();

    void set_reflective_brdf(PerfectSpecular* reflc);
    void set_specular_btdf(PerfectTransmitter* trans);
    PerfectSpecular* get_reflective_brdf() const;
    PerfectTransmitter* get_specular_btdf() const;

    void set_kr(const float k);
    void set_kt(const float k);
    void set_ior(const float k);

    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);

private:
    PerfectSpecular* reflective_brdf;
    PerfectTransmitter* specular_btdf;
};