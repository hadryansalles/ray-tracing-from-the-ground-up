#pragma once

#include "Material.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"

class Phong: public Material{
public:
    Phong(Lambertian* ambient_brdf_ = NULL, Lambertian* diffuse_brdf_ = NULL, GlossySpecular* specular_brdf_ = NULL);
    Phong(const Phong& m);
    virtual Phong* clone() const;
    virtual Phong* clone(RGBColor new_color) const;
    Phong& operator=(const Phong& rhs);
    ~Phong();

    Lambertian* get_ambient_brdf() const;
    void set_ambient_brdf(Lambertian* ambient_brdf_);

    Lambertian* get_diffuse_brdf() const;
    void set_diffuse_brdf(Lambertian* diffuse_brdf_);

    GlossySpecular* get_specular_brdf() const;
    void set_specular_brdf(GlossySpecular* specular_brdf_);

    void set_ka(const float k);
    void set_kd(const float k);
    void set_ks(const float k);
    void set_exp(const float exp_);
    void set_cd(const RGBColor& c);
    void set_cd(const float r, const float g, const float b);
    void set_cd(const float a); 
        
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);

private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    GlossySpecular* specular_brdf;
};