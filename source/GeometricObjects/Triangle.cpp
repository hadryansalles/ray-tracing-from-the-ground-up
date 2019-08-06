#include "Triangle.hpp"

Triangle::Triangle()
    : GeometricObject(NULL)
    , v0(0)
    , v1(0)
    , v2(0)
    , normal(0) 
{}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* material_p)
    : GeometricObject(material_p)
    , v0(a)
    , v1(b)
    , v2(c) {
    normal = (v1 - v0) ^ (v2 - v0);
    normal.normalize();
}

Triangle::Triangle(const Triangle& triangle)
    : GeometricObject(triangle)
    , v0(triangle.v0)
    , v1(triangle.v1)
    , v2(triangle.v2)
    , normal(triangle.normal)
{}

Triangle& Triangle::operator=(const Triangle& rhs){
    if(this == &rhs){
        return (*this);
    }
    GeometricObject::operator=(rhs);
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    normal = rhs.normal;
    return (*this);
}

Triangle* Triangle::clone() const {
    return (new Triangle(*this));
}

BBox Triangle::get_bounding_box() const {
    double delta = 0.00001;
    return (BBox(Point3D(min(min(v0.x, v1.x), v2.x) - delta, 
                         min(min(v0.y, v1.y), v2.y) - delta,
                         min(min(v0.z, v1.z), v2.z) - delta),
                 Point3D(max(max(v0.x, v1.x), v2.x) + delta,
                         max(max(v0.y, v1.y), v2.y) + delta,
                         max(max(v0.z, v1.z), v2.z) + delta)));
}

bool Triangle::hit(const Ray& ray, float& t, ShadeRec& s) const {
    float a = v0.x - v1.x;
    float b = v0.x - v2.x;
    float c = ray.d.x;
    float d = v0.x - ray.o.x;
    
    float e = v0.y - v1.y;
    float f = v0.y - v2.y;
    float g = ray.d.y;
    float h = v0.y - ray.o.y;
    
    float i = v0.z - v1.z;
    float j = v0.z - v2.z;
    float k = ray.d.z; 
    float l = v0.z - ray.o.z;

    float m = f*k - g*j;
    float n = h*k - g*l;
    float p = f*l - h*j;
    float q = g*i - e*k;
    float r = e*j - f*i;

    float inv_denom = 1.0 / (a*m + b*q + c*r);
    float e1 = d*m - b*n - c*p;
    float beta = e1*inv_denom;

    if(beta < 0){
        return false;
    }
    
    float u = e*l - h*i;
    float e2 = a*n + d*q + c*r;
    float gamma = e2*inv_denom;

    if(gamma < 0){
        return false;
    }

    if(beta + gamma > 1.0){
        return false;
    }

    float e3 = a*p - b*u + d*r;
    float v = e3*inv_denom;

    if(v < kEpsilon){
        return false;
    }

    t = v;
    s.normal = normal;
    s.local_hit_point = ray.o + t*ray.d;
    return true;
}