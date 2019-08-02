#include "Lambertian.hpp"

Lambertian::Lambertian(float kd_, RGBColor cd_):
    BRDF(),
    kd(kd_),
    cd(cd_)
{}

Lambertian::Lambertian(const Lambertian& lamb):
    BRDF(lamb),
    kd(lamb.kd),
    cd(lamb.cd)
{}

Lambertian* Lambertian::clone() const{
    return (new Lambertian(*this));
}

Lambertian& Lambertian::operator=(const Lambertian& rhs){
    if(this == &rhs){
        return (*this);
    }
    BRDF::operator=(rhs);
    kd = rhs.kd;
    cd = rhs.cd;
    return (*this);
}

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

RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return (kd * cd);
}