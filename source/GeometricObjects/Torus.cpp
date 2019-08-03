#include "Torus.hpp"

Torus::Torus(Material* material_p, BBox bbox_)
    : GeometricObject(material_p)
    , bbox(bbox_)
{}

Torus::Torus(const Torus& torus)
    : GeometricObject(torus)
    , bbox(torus.bbox)
{}

Torus& Torus::operator=(Torus& rhs){
    if(this == &rhs){
        return *this;
    }
    GeometricObject::operator=(rhs);
    bbox = rhs.bbox;
    return(*this);
}

Torus* Torus::clone(void) const{
    return (new Torus(*this));
}

bool Torus::hit(const Ray& ray, float& t, ShadeRec& s) const {
    if(!bbox.hit(ray)){
        return false;
    }
    // ...

    return false;
}