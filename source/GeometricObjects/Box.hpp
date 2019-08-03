#pragma once

#include "GeometricObject.hpp"

class Box : public GeometricObject {
public:
    Box(Material* material_p = NULL);
    Box(Point3D p0_, Point3D dimensions_, Material* material_p = NULL);
    Box(const Box& box);
    
    virtual Box* clone() const;
    Box& operator= (Box& rhs);

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;
    Normal get_normal(const int face_hit) const;

    void set_p0(const Point3D p0_);
    Point3D get_p0() const;
    
    void set_p1(const Point3D p1_);
    Point3D get_p1() const;
    
    void set_dimensions(const Point3D dimensions_);
    Point3D get_dimensions() const;

    void set_dimension_x(const float width);
    void set_dimension_y(const float height);
    void set_dimension_z(const float depth);

protected:
    Point3D p0;
    Point3D p1;
    Point3D dimensions;
};  