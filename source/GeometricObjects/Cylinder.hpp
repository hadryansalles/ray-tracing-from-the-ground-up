#pragma once

#include "Compound.hpp"
#include "OpenCylinder.hpp"
#include "Disk.hpp"

class Cylinder : public Compound {
public:
    Cylinder();
    Cylinder(float y0_, float y1_, float radius_);
    Cylinder(const Cylinder& cc);
    Cylinder* clone() const;
    Cylinder& operator=(const Cylinder& rhs);

    void set_radius(const float radius_);
    float get_radius() const;

    void set_y0(const float y0_);
    float get_y0() const;  

    void set_y1(const float y1_);
    float get_y1() const;  

    virtual BBox get_bounding_box() const;
    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

protected:
    Disk* top_disk;
    OpenCylinder* openc;
    Disk* bottom_disk;
    BBox bbox;

    void set_bbox();
};