#include "Transparent.hpp"

Transparent::Transparent()
    : Phong()
    , reflective_brdf(new PerfectSpecular())
    , specular_btdf(new PerfectTransmitter())
{}

Transparent::Transparent(const Transparent& rhs)
    : Phong(rhs) 
    , reflective_brdf(NULL)
    , specular_btdf(NULL) {
    if(rhs.get_specular_btdf()){
        specular_btdf = rhs.get_specular_btdf()->clone();
    }
    else{
        specular_btdf = new PerfectTransmitter();
    }
    if(rhs.get_reflective_brdf()){
        reflective_brdf = rhs.get_reflective_brdf()->clone();
    }
    else{
        reflective_brdf = new PerfectSpecular();
    }
}
Transparent& Transparent::operator=(const Transparent& rhs){
    if(this == &rhs){
        return (*this);
    }
    Phong::operator=(rhs);
    if(reflective_brdf){
        delete reflective_brdf;
        reflective_brdf = NULL;
    } 
    if(specular_btdf){
        delete specular_btdf;
        specular_btdf = NULL;
    }
    if(rhs.get_specular_btdf()){
        specular_btdf = rhs.get_specular_btdf()->clone();
    }
    if(rhs.get_reflective_brdf()){
        reflective_brdf = rhs.get_reflective_brdf()->clone();
    }
    return (*this);
}

Transparent* Transparent::clone() const{
    return (new Transparent(*this));
}

Transparent::~Transparent(){
    if(reflective_brdf){
        delete reflective_brdf;
        reflective_brdf = NULL;
    }
    if(specular_btdf){
        delete specular_btdf;
        specular_btdf = NULL;
    }
}

void Transparent::set_reflective_brdf(PerfectSpecular* reflc){
    if(reflective_brdf){
        delete reflective_brdf;
    }
    reflective_brdf = reflc;
}

void Transparent::set_specular_btdf(PerfectTransmitter* trans){
    if(specular_btdf){
        delete specular_btdf;
    }
    specular_btdf = trans;
}

PerfectSpecular* Transparent::get_reflective_brdf() const{
    return reflective_brdf;   
}

PerfectTransmitter* Transparent::get_specular_btdf() const{
    return specular_btdf;
}

void Transparent::set_kr(const float k){
    reflective_brdf->set_kr(k);
}

void Transparent::set_kt(const float k){
    specular_btdf->set_kt(k);
}

void Transparent::set_ior(const float k){
    specular_btdf->set_ior(k);
}

RGBColor Transparent::shade(ShadeRec& sr){
    RGBColor L(Phong::shade(sr));
    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);
    if(specular_btdf->tir(sr)){
        L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth+1);
    }
    else{
        Vector3D wt;
        RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
        Ray transmitted_ray(sr.hit_point, wt);
        L += fr*sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth+1)
             * fabs(sr.normal * wi);
        L += ft*sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth+1)
             * fabs(sr.normal * wt);
    }
    return L;
}

RGBColor Transparent::area_light_shade(ShadeRec& sr){
    RGBColor L(Phong::shade(sr));
    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);
    if(specular_btdf->tir(sr)){
        L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth+1);
    }
    else{
        Vector3D wt;
        RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
        Ray transmitted_ray(sr.hit_point, wt);
        L += fr*sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth+1)
             * fabs(sr.normal * wi);
        L += ft*sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth+1)
             * fabs(sr.normal * wt);
    }
    return L;
}