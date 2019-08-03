#pragma once

#include "../Utilities/Ray.hpp"
#include "../Utilities/Constants.hpp"

class BBox{
public:
    BBox(Point3D p0_ = Point3D(0), Point3D p1_ = Point3D(0));
    BBox(const BBox& bbox);
    BBox* clone();
    BBox& operator= (BBox& rhs);
    ~BBox();

    bool hit(const Ray& ray) const;
    
    Point3D p0;
    Point3D p1;
};