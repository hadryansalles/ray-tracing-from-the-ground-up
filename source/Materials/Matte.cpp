#include "Matte.hpp"

Matte::Matte(Lambertian* ambient_brdf_, Lambertian* diffuse_brdf_):
    ambient_brdf(ambient_brdf_),
    diffuse_brdf(diffuse_brdf_)
{
    if(ambient_brdf_ == NULL){
        ambient_brdf = new Lambertian();
    }
    if(diffuse_brdf == NULL){
        diffuse_brdf_ = new Lambertian();
    }
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
    ambient_brdf = ambient_brdf_;
}

Lambertian* Matte::get_diffuse_brdf() const{
    return diffuse_brdf;
}

void Matte::set_diffuse_brdf(Lambertian* diffuse_brdf_){
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
        Vector3D wi = sr.w.lighst[j]->get_direction(sr);
        float ndotwi = sr.normal*wi;
        if(ndotwi > 0.0){
            L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*ndotwi;
        }
    }
    return L;
}