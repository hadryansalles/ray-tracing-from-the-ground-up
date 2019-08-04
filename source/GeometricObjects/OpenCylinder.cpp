#include "OpenCylinder.hpp"

OpenCylinder::OpenCylinder(Material* material_p)
    : GeometricObject(material_p)
    , begin(0)
    , height(0)
    , radius(0)
{}

OpenCylinder::OpenCylinder(Point3D begin_, float height_, float radius_, Material* material_p)
    : GeometricObject(material_p)
    , begin(begin_)
    , height(height_)
    , radius(radius_)
{}

OpenCylinder::OpenCylinder(const OpenCylinder& disk)
: GeometricObject(disk)
    , begin(disk.begin)
    , height(disk.height)
    , radius(disk.radius)
{}

OpenCylinder& OpenCylinder::operator=(const OpenCylinder& rhs){
    if(this == &rhs){
        return(*this);
    }
    GeometricObject::operator=(rhs);
    begin = rhs.begin;
    height = rhs.height;
    radius = rhs.radius;
    return(*this);
}

OpenCylinder* OpenCylinder::clone() const{
    return (new OpenCylinder(*this));
}

bool OpenCylinder::hit(const Ray& ray, float& t, ShadeRec& s) const{
    Point3D d(ray.d.x, ray.d.y, ray.d.z);
    Point3D o(ray.o);

    float a = d.x*d.x + d.z*d.z;
    float b = 2.0*(o.x*d.x + o.z*d.z);
    float c = o.x*o.x + o.z*o.z - radius*radius;
    float disc = b*b - 4.0*a*c;
    float myt;

    if(disc >= 0){
        myt = (-b -sqrt(disc)) / (2.0*a);
        Point3D hit_p = o + d*myt;
        if(myt > kEpsilon){
            if(hit_p.y > begin.y 
            && hit_p.y < (begin.y+height)){
                t = myt;
                s.normal = Normal(hit_p.x/radius, 0.0, hit_p.z/radius);
                if (-ray.d * s.normal < 0.0) s.normal = -s.normal;
                s.local_hit_point = o + t*d;
                return true;
            }
        }   
        myt = (-b + sqrt(disc)) / (2.0*a);
        hit_p = o + d*myt;
        if(t > kEpsilon){
            if(hit_p.y > begin.y 
            && hit_p.y < (begin.y+height)){
                t = myt;
                s.normal = Normal(hit_p.x/radius, 0.0, hit_p.z/radius);
                if (-ray.d * s.normal < 0.0){
                    s.normal = -s.normal;
                }
                s.local_hit_point = o + t*d;
                return true;
            }
        }
    }
    return false;
}

void OpenCylinder::set_begin(const Point3D begin_){
    begin = begin_;
}

Point3D OpenCylinder::get_begin() const{
    return begin;
}

void OpenCylinder::set_radius(const float radius_){
    radius = radius_;
}

float OpenCylinder::get_radius() const{
    return radius;
}

void OpenCylinder::set_height(const float height_){
    height = height_;
}

float OpenCylinder::get_height() const{
    return height;
}