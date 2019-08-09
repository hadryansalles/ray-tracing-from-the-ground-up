#include "Emissive.hpp"

Emissive::Emissive(const float ls_, const RGBColor ce_)
    : Material()
    , ls(ls_)
    , ce(ce_)
{}

Emissive::Emissive(const Emissive& emissive)
    : Material(emissive)
    , ls(emissive.ls)
    , ce(emissive.ce)
{}

Emissive& Emissive::operator=(const Emissive& rhs) {
    if(this == &rhs){
        return (*this);
    }
    Material::operator=(rhs);
    ls = rhs.ls;
    ce = rhs.ce;
    return (*this);
}

Emissive* Emissive::clone() const {
    return (new Emissive(*this));
}

void Emissive::scale_radiance(const float ls_) {
    ls = ls_;
}

void Emissive::set_ce(const float r, const float g, const float b) {
    ce = RGBColor(r, g, b);
}

void Emissive::set_ce(const float a) {
    ce = RGBColor(a);
}

void Emissive::set_ce(const RGBColor ce_) {
    ce = ce_;
}

RGBColor Emissive::get_Le(ShadeRec& sr) const {
    return ls*ce;
}

RGBColor Emissive::shade(ShadeRec& sr) {
    return black;
}

RGBColor Emissive::area_light_shade(ShadeRec& sr) {
    if(-sr.normal*sr.ray.d > 0.0){
        return (ls*ce);
    }
    else{
        return black;
    }
}