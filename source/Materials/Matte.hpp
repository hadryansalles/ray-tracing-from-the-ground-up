#pragma once

#include "Material.hpp"
#include "../BRDF/Lambertian.hpp"

class Matte: public Material{
public:
    Matte(Lambertian* ambient_brdf_ = NULL, Lambertian* diffuse_brdf_ = NULL);
    Matte(const Matte& m);
    virtual Matte* clone() const;
    Matte* clone(RGBColor new_color) const;
    Matte& operator=(const Matte& rhs);
    ~Matte();

    Lambertian* get_ambient_brdf() const;
    void set_ambient_brdf(Lambertian* ambient_brdf_);

    Lambertian* get_diffuse_brdf() const;
    void set_diffuse_brdf(Lambertian* diffuse_brdf_);

    void set_ka(const float k);
    void set_kd(const float k);
    void set_cd(const RGBColor& c);
    virtual RGBColor shade(ShadeRec& sr);

private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
};