#include "BBox.hpp"

BBox::BBox(Point3D p0_, Point3D p1_)
    : p0(p0_)
    , p1(p1_)
{}

BBox::BBox(const BBox& bbox)
    : p0(bbox.p0)
    , p1(bbox.p1)
{}

BBox* BBox::clone() const{
    return (new BBox(*this));
}

BBox& BBox::operator= (BBox& rhs){
    if(this == &rhs){
        return *this;
    }
    p0 = rhs.p0;
    p1 = rhs.p1;
    return *this;
}

BBox::~BBox()
{}

bool BBox::hit(const Ray& ray) const{
    Point3D o(ray.o);
    Point3D d(ray.d.x, ray.d.y, ray.d.z); 
    Point3D t_min;
    Point3D t_max;

    double a = 1.0 / d.x;
    if(a >= 0){
        t_min.x = (p0.x - o.x) * a;
        t_max.x = (p1.x - o.x) * a; 
    }
    else{
        t_min.x = (p1.x - o.x) * a;
        t_max.x = (p0.x - o.x) * a;
    }
    double b = 1.0 / d.y;
    if(b >= 0){
        t_min.y = (p0.y - o.y) * b;
        t_max.y = (p1.y - o.y) * b; 
    }
    else{
        t_min.y = (p1.y - o.y) * b;
        t_max.y = (p0.y - o.y) * b;
    } 
    double c = 1.0 / d.z;
    if(c >= 0){
        t_min.z = (p0.z - o.z) * c;
        t_max.z = (p1.z - o.z) * c; 
    }
    else{
        t_min.z = (p1.z - o.z) * c;
        t_max.z = (p0.z - o.z) * c;
    }
    double t0, t1;
    // finding largest
    if(t_min.x > t_min.y){
        t0 = t_min.x;
    }
    else{
        t0 = t_min.y;
    }
    if(t_min.z > t0){
        t0 = t_min.z;
    }
    // find smallest
    if(t_max.x < t_max.y){
        t1 = t_max.x;
    }
    else{
        t1 = t_max.y;
    }
    if(t_max.z < t1){
        t1 = t_max.z;
    }
    return (t0 < t1 && t1 > kEpsilon);
}