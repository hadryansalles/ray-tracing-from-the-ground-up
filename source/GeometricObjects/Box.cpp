#include "Box.hpp"

Box::Box(Material* material_p)
    : GeometricObject(material_p)
    , p0(0)
    , p1(0)
    , dimensions(0)
{}

Box::Box(Point3D p0_, Point3D p1_, Material* material_p)
    : GeometricObject(material_p)
    , p0(p0_)
    , p1(p1_)
    , dimensions(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z)
{}

Box::Box(const Box& box)
    : GeometricObject(box)
    , p0(box.p0)
    , p1(box.p1)
    , dimensions(box.dimensions)
{}
    
Box* Box::clone() const{
    return (new Box(*this));
}

Box& Box::operator= (Box& rhs){
    if(this == &rhs){
        return (*this);
    }
    GeometricObject::operator=(rhs);

}

void Box::set_p0(const Point3D p0_){
    p0 = p0_;
}

Point3D Box::get_p0() const{
    return p0;
}

void Box::set_p1(const Point3D p1_){
    p1 = p1_;
    dimensions = p1 - Vector3D(p0);
}

Point3D Box::get_p1() const{
    return p1;
}

void Box::set_dimensions(const Point3D dimensions_){
    dimensions = dimensions_;
    p1 = Point3D(p0 + dimensions);
}

Point3D Box::get_dimensions() const{
    return dimensions;
}

bool Box::hit(const Ray& ray, float& t, ShadeRec& s) const{
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
    int face_in, face_out;
    // finding largest
    if(t_min.x > t_min.y){
        t0 = t_min.x;
        face_in = (a >= 0.0) ? 0 : 3;
    }
    else{
        t0 = t_min.y;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if(t_min.z > t0){
        t0 = t_min.z;
        face_in = (c >= 0.0) ? 2 : 5;
    }
    // find smallest
    if(t_max.x < t_max.y){
        t1 = t_max.x;
        face_out = (a >= 0.0) ? 3 : 0;
    }
    else{
        t1 = t_max.y;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if(t_max.z < t1){
        t1 = t_max.z;
        face_out = (c >= 0.0) ? 5 : 2;
    }
    if(t0 < t1 && t1 > kEpsilon){
        if(t0 > kEpsilon){
            t = t0;
            s.normal = get_normal(face_in);
        }
        else{
            t = t1;
            s.normal = get_normal(face_out);
        }
        s.local_hit_point = ray.o + t*ray.d;
        return true;
    }
    else{
        return false;
    }
}

bool Box::shadow_hit(const Ray& ray, float& tmin) const {
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
    int face_in, face_out;
    // finding largest
    if(t_min.x > t_min.y){
        t0 = t_min.x;
        face_in = (a >= 0.0) ? 0 : 3;
    }
    else{
        t0 = t_min.y;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if(t_min.z > t0){
        t0 = t_min.z;
        face_in = (c >= 0.0) ? 2 : 5;
    }
    // find smallest
    if(t_max.x < t_max.y){
        t1 = t_max.x;
        face_out = (a >= 0.0) ? 3 : 0;
    }
    else{
        t1 = t_max.y;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if(t_max.z < t1){
        t1 = t_max.z;
        face_out = (c >= 0.0) ? 5 : 2;
    }
    if(t0 < t1 && t1 > kEpsilon){
        if(t0 > kEpsilon){
            tmin = t0;
        }
        else{
            tmin = t1;
        }
        return true;
    }
    return false;
}

Normal Box::get_normal(const int face_hit) const{
    switch (face_hit) {
        case 0: return (Normal(-1, 0, 0)); // -x face
        case 1: return (Normal(0, -1, 0)); // -y face
        case 2: return (Normal(0, 0, -1)); // -z face
        case 3: return (Normal(1, 0, 0));  // +x face
        case 4: return (Normal(0, 1, 0));  // +y face
        case 5: return (Normal(0, 0, 1));  // +z face
    }
}