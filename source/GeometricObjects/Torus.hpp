#pragma once

#include "GeometricObject.hpp"
#include "BBox.hpp"

class Torus : public GeometricObject {
public:
    Torus(Material* material_p = NULL, BBox bbox_ = BBox());
    Torus(const Torus& torus);
    Torus& operator=(Torus& rhs);
    virtual Torus* clone(void) const;
    ~Torus();
    
    bool hit(const Ray& ray, float& t, ShadeRec& s) const;

protected:
    BBox bbox;
};