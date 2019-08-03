#pragma once

#include "BBox.hpp"

class Box : public BBox {
    Box(Point3D p0_ = Point3D(0), Point3D p1_ = Point3D(0));
    Box(const Box& box);
    virtual Box* clone() const;
    Box& operator= (Box& rhs);

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
    Normal get_normal(const int face_hit) const;
};  