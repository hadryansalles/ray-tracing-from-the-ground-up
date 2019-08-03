#include "Box.hpp"

Box::Box(Point3D p0_, Point3D p1_)
    : BBox(p0_, p1_)
{}

Box::Box(const Box& box)
    : BBox(box)
{}

Box* Box::clone() const{
    return (new Box(*this));
}

Box& Box::operator= (Box& rhs){
    if(this == &rhs){
        return *this;
    }
    BBox::operator=(rhs);
    return *this;
}

bool Box::hit(const Ray& ray, double& tmin, ShadeRec& sr) const{
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
            sr.normal = get_normal(face_in);
        }
        else{
            tmin = t1;
            sr.normal = get_normal(face_out);
        }
        sr.local_hit_point = ray.o + tmin*ray.d;
        return true;
    }
    else{
        return false;
    }
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