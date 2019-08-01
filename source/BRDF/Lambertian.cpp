#include "Lambertian.hpp"

Lambertian::Lambertian(float kd_, RGBColor cd_):
    BRDF(),
    kd(kd_),
    cd(cd_)
{}

float Lambertian::get_kd() const{
    return kd;
}

void Lambertian::set_kd(const float kd){
    this->kd = kd;
}

RGBColor Lambertian::get_cd() const{
    return cd;
}

void Lambertian::set_cd(const RGBColor cd){
    this->cd = cd;
}

RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const{
    return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const{
    
}

RGBColor Lambertian::rho(ShadeRec& sr, const Vector3D& wo) const{
    return (kd * cd);
}