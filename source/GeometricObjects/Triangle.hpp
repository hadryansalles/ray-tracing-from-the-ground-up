#pragma once

#include "GeometricObject.hpp"

class Triangle : public GeometricObject {
public:
    Point3D v0, v1, v2;
    Normal normal;

    Triangle();
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* material_p = NULL); 
    Triangle(const Triangle& triangle);
    Triangle& operator=(const Triangle& rhs);
    Triangle* clone() const;

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const; 
};