#pragma once

#include "../Utilities/Ray.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Utilities/Constants.hpp"

class BBox{
public:
    BBox(Point3D p0_ = Point3D(0), Point3D p1_ = Point3D(0));
    BBox(const BBox& bbox);
    virtual BBox* clone() const;
    BBox& operator= (BBox& rhs);
    virtual ~BBox();

    virtual bool hit(const Ray& ray) const;
    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
    
    Point3D p0;
    Point3D p1;
};