  #include "PerfectSpecular.hpp"
  
PerfectSpecular::PerfectSpecular(float kr_, RGBColor cr_)
    : BRDF()
    , kr(kr_)
    , cr(cr_)
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& perf)
    : BRDF(perf)
    , kr(perf.kr)
    , cr(perf.cr)
{}

PerfectSpecular* PerfectSpecular::clone() const { 
    return (new PerfectSpecular(*this));
}

PerfectSpecular& PerfectSpecular::operator=(const PerfectSpecular& rhs){
    if(this == &rhs){
        return (*this);
    }
    BRDF::operator=(rhs);
    kr = rhs.kr;
    cr = rhs.cr;
    return (*this);
}

float PerfectSpecular::get_kr() const{
    return kr;
}

void PerfectSpecular::set_kr(const float kr){
    this->kr = kr;
}

RGBColor PerfectSpecular::get_cr() const{
    return cr;
}

void PerfectSpecular::set_cr(const RGBColor cr){
    this->cr = cr;
}

RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const{
    float ndotwo = sr.normal*wo;
    wi = (-wo + 2.0*sr.normal*ndotwo);
    return (kr*cr/(sr.normal*wi));
}  