#include "GlossySpecular.hpp"
#include "../Utilities/Constants.hpp"

GlossySpecular::GlossySpecular(float kd_, float exp_, RGBColor cd_):
    BRDF(),
    kd(kd_),
    E(exp_),
    cd(cd_)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& lamb):
    BRDF(lamb),
    kd(lamb.kd),
    E(lamb.E),
    cd(lamb.cd)
{}

GlossySpecular* GlossySpecular::clone() const{
    return (new GlossySpecular(*this));
}

GlossySpecular& GlossySpecular::operator=(const GlossySpecular& rhs){
    if(this == &rhs){
        return (*this);
    }
    BRDF::operator=(rhs);
    kd = rhs.kd;
    E = rhs.E;
    cd = rhs.cd;
    return (*this);
}

float GlossySpecular::get_kd() const{
    return kd;
}

void GlossySpecular::set_kd(const float kd){
    this->kd = kd;
}

void GlossySpecular::set_exp(const float exp_){
    this->E = exp_;
}

float GlossySpecular::get_exp() const{
    return E;
}

RGBColor GlossySpecular::get_cd() const{
    return cd;
}

void GlossySpecular::set_cd(const RGBColor cd){
    this->cd = cd;
}

RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    RGBColor L;
    float ndotwi = sr.normal*wi;
    Vector3D r(-wi + 2.0*sr.normal*ndotwi);
    float rdotwo = r*wo;
    if(rdotwo > 0.0){
        L = cd*kd*pow(rdotwo, E);
    }
    return (L);
}

RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return (black);
}