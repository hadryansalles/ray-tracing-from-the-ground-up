#include "OpenCylinder.hpp"

OpenCylinder::OpenCylinder(Material* material_p)
    : GeometricObject(material_p)
    , y0(0)
    , y1(1)
    , radius(1)
{}

OpenCylinder::OpenCylinder(float y0_, float y1_, float radius_, Material* material_p)
    : GeometricObject(material_p)
    , y0(y0_)
    , y1(y1_)
    , radius(radius_)
{}

OpenCylinder::OpenCylinder(const OpenCylinder& disk)
: GeometricObject(disk)
    , y0(disk.y0)
    , y1(disk.y1)
    , radius(disk.radius)
{}

OpenCylinder& OpenCylinder::operator=(const OpenCylinder& rhs){
    if(this == &rhs){
        return(*this);
    }
    GeometricObject::operator=(rhs);
    y0 = rhs.y0;
    y1 = rhs.y1;
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
            if(hit_p.y > y0 && hit_p.y < y1){
                t = myt;
                s.normal = Normal(hit_p.x/radius, 0.0, hit_p.z/radius);
                if (-ray.d * s.normal < 0.0) s.normal = -s.normal;
                s.local_hit_point = o + t*d;
                return true;
            }
        }   
        myt = (-b + sqrt(disc)) / (2.0*a);
        hit_p = o + d*myt;
        if(myt > kEpsilon){
            if(hit_p.y > y0 && hit_p.y < y1){
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

bool OpenCylinder::shadow_hit(const Ray& ray, float& tmin) const{
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
            if(hit_p.y > y0 && hit_p.y < y1){
                tmin = myt;
                return true;
            }
        }   
        myt = (-b + sqrt(disc)) / (2.0*a);
        hit_p = o + d*myt;
        if(myt > kEpsilon){
            if(hit_p.y > y0 && hit_p.y < y1){
                tmin = myt;
                return true;
            }
        }
    }
    return false;
}

void OpenCylinder::set_y0(const float y0_){
    y0 = y0_;
}

float OpenCylinder::get_y0() const{
    return y0;
} 

void OpenCylinder::set_y1(const float y1_){
    y1 = y1_;
}

float OpenCylinder::get_y1() const{
    return y1;
} 

void OpenCylinder::set_radius(const float radius_){
    radius = radius_;
}

float OpenCylinder::get_radius() const{
    return radius;
}