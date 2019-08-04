#pragma once

#include "GeometricObject.hpp"
#include "../Utilities/Maths.hpp"

class OpenCylinder : public GeometricObject {
public:
    OpenCylinder(Material* material_p = NULL);
    OpenCylinder(Point3D begin_, float height_, float radius_, Material* material_p = NULL);
    OpenCylinder(const OpenCylinder& disk);

    OpenCylinder& operator=(const OpenCylinder& rhs);
    virtual OpenCylinder* clone() const;

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

    void set_begin(const Point3D begin_);
    Point3D get_begin() const;

    void set_radius(const float radius_);
    float get_radius() const;  

    void set_height(const float height_);
    float get_height() const;

protected:
    Point3D begin;
    float height;
    float radius;
};