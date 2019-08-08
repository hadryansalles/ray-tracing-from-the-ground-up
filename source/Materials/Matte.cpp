#include "Matte.hpp"

#include "../World/World.hpp"

Matte::Matte(Lambertian* ambient_brdf_, Lambertian* diffuse_brdf_):
    Material()
{
    if(ambient_brdf_ == NULL){
        ambient_brdf = new Lambertian(0,25);
    }
    if(diffuse_brdf_ == NULL){
        diffuse_brdf = new Lambertian(0,75);
    }
}

Matte::Matte(const Matte& m):
    Material(m)
{   
    if(m.ambient_brdf){
        ambient_brdf = m.ambient_brdf->clone();
    }
    else{
        ambient_brdf = new Lambertian;
    }

    if(m.diffuse_brdf){
        diffuse_brdf = m.diffuse_brdf->clone();
    }
    else{
        diffuse_brdf = new Lambertian;
    }
}

Matte* Matte::clone() const{
    return (new Matte(*this));
}
Matte* Matte::clone(RGBColor new_color) const {
    Matte* new_matte = new Matte(*this);
    new_matte->set_cd(new_color);
    return (new_matte);
}

Matte& Matte::operator=(const Matte& rhs){
    if(this == &rhs){
        return (*this);
    }
    Material::operator=(rhs);
    if(ambient_brdf && rhs.ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = rhs.ambient_brdf->clone();
    }
    if(diffuse_brdf && rhs.diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = rhs.diffuse_brdf->clone();
    }
    return(*this);
}

Matte::~Matte(){
    if(ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if(diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
}

Lambertian* Matte::get_ambient_brdf() const{
    return ambient_brdf;
}

void Matte::set_ambient_brdf(Lambertian* ambient_brdf_){
    if(ambient_brdf_ != NULL)
        ambient_brdf = ambient_brdf_;
}

Lambertian* Matte::get_diffuse_brdf() const{
    return diffuse_brdf;
}

void Matte::set_diffuse_brdf(Lambertian* diffuse_brdf_){
    if(diffuse_brdf_ != NULL)
        diffuse_brdf = diffuse_brdf_;
}

void Matte::set_ka(const float k){
    ambient_brdf->set_kd(k);
}

void Matte::set_kd(const float k){
    diffuse_brdf->set_kd(k);
}

void Matte::set_cd(const RGBColor& c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}   

RGBColor Matte::shade(ShadeRec& sr){
    Vector3D wo = -sr.ray.d;
    RGBColor L = ambient_brdf->rho(sr, wo)*sr.w.ambient_ptr->L(sr);
    int num_lights = sr.w.lights.size();

    for(int j = 0; j < num_lights; j++){
        Vector3D wi = sr.w.lights[j]->get_direction(sr);
        float ndotwi = sr.normal*wi;
        bool in_shadow = false;
        if(ndotwi > 0.0){
            if(sr.w.lights[j]->get_shadows()){
                Ray shadowRay(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }
            if(!in_shadow) {
                L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*ndotwi;
            }
        }
    }
    return L;
}