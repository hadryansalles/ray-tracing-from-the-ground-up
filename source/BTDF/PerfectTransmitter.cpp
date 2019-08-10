#include "PerfectTransmitter.hpp"

PerfectTransmitter::PerfectTransmitter(Sampler* sampler, const float kt_, const float ior_)
    : BTDF(sampler)
    , kt(kt_)
    , ior(ior_) 
{}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& perf)
    : BTDF(perf)
    , kt(perf.kt)
    , ior(perf.ior)
{}

PerfectTransmitter& PerfectTransmitter::operator=(const PerfectTransmitter& rhs){
    if(this == &rhs){
        return (*this);
    }
    BTDF::operator=(rhs);
    kt = rhs.kt;
    ior = rhs.ior;
    return(*this);
}

PerfectTransmitter* PerfectTransmitter::clone() const{
    return (new PerfectTransmitter(*this));
}

RGBColor PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    return white;
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt) const{
    Normal n(sr.normal);
    float cos_theta_i = n*wo;
    float eta = ior;
    if(cos_theta_i < 0.0){
        cos_theta_i = -cos_theta_i;
        n = -n;
        eta = 1.0/eta;
    }
    float temp = 1.0 - (1.0 - cos_theta_i*cos_theta_i)/(eta*eta);
    float cos_theta2 = sqrt(temp);
    wt = -wo / eta - (cos_theta2-cos_theta_i/eta)*n;
    return (kt/(eta*eta)*white/fabs(sr.normal*wt));
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt, float& pdf) const{

}

RGBColor PerfectTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return white;
}

bool PerfectTransmitter::tir(const ShadeRec& sr) const{
    Vector3D wo(-sr.ray.d);
    float cos_thteai = sr.normal*wo;
    float eta = ior;
    if(cos_thteai < 0.0){
        eta = 1.0/eta;
    }
    return ((1.0 - (1.0 - cos_thteai*cos_thteai)/(eta*eta)) < 0.0);
}

void PerfectTransmitter::set_kt(const float k){
    kt = k;
}

float PerfectTransmitter::get_kt() const{
    return kt;
}

void PerfectTransmitter::set_ior(const float ior_){
    ior = ior_;
}

float PerfectTransmitter::get_ior() const{
    return ior;
}