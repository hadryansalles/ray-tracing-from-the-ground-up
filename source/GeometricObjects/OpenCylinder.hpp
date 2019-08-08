#pragma once

#include "GeometricObject.hpp"
#include "../Utilities/Maths.hpp"

class OpenCylinder : public GeometricObject {
public:
    OpenCylinder(Material* material_p = NULL);
    OpenCylinder(float y0_, float y1_, float radius_, Material* material_p = NULL);
    OpenCylinder(const OpenCylinder& disk);

    OpenCylinder& operator=(const OpenCylinder& rhs);
    virtual OpenCylinder* clone() const;

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;
    virtual bool shadow_hit(const Ray& ray, float& tmin) const;
    
    void set_y0(const float y0_);
    float get_y0() const;  

    void set_y1(const float y1_);
    float get_y1() const;  

    void set_radius(const float radius_);
    float get_radius() const;  

protected:
    float y0;
    float y1;
    float radius;
};