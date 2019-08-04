#pragma once

#include "GeometricObject.hpp"

class Disk : public GeometricObject {
public:
    Disk(Material* material_p = NULL);
    Disk(Point3D center_, Normal normal_, float radius_, Material* material_p = NULL);
    Disk(const Disk& disk);

    Disk& operator=(const Disk& rhs);
    virtual Disk* clone() const;

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

    void set_center(const Point3D center_);
    Point3D get_center() const;

    void set_radius(const float radius_);
    float get_radius() const;  

    void set_normal(const Normal normal_);
    Normal get_normal() const;

protected:
    Point3D center;
    Normal normal;
    float radius;
};