#include "FlatMeshTriangle.hpp"

FlatMeshTriangle::FlatMeshTriangle(Mesh* mesh_ptr_, const int i0, const int i1, const int i2)
    : MeshTriangle(mesh_ptr_, i0, i1, i2)
{}

FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle& flat_mesh)
    : MeshTriangle(flat_mesh)
{}

FlatMeshTriangle& FlatMeshTriangle::operator=(const FlatMeshTriangle& rhs){
    if(this == &rhs){
        return (*this);
    }
    MeshTriangle::operator=(rhs);
    return (*this);
}

FlatMeshTriangle* FlatMeshTriangle::clone() const {
    return (new FlatMeshTriangle(*this));
}
FlatMeshTriangle::~FlatMeshTriangle(){

}

bool FlatMeshTriangle::hit(const Ray& ray, float& t, ShadeRec& s) const{
    Point3D v0(mesh_ptr->vertices[index0]);
    Point3D v1(mesh_ptr->vertices[index1]);
    Point3D v2(mesh_ptr->vertices[index2]);

    double a = v0.x - v1.x;
    double b = v0.x - v2.x;
    double c = ray.d.x;
    double d = v0.x - ray.o.x;
    
    double e = v0.y - v1.y;
    double f = v0.y - v2.y;
    double g = ray.d.y;
    double h = v0.y - ray.o.y;

    double i = v0.z - v1.z;
    double j = v0.z - v2.z;
    double k = ray.d.z;
    double l = v0.z - ray.o.z;

    double m = f*k - g*j;
    double n = h*k - g*l;
    double p = f*l - h*j;
    double q = g*i - e*k;
    double r = e*l - h*i;
    double o = e*j - f*i;

    double inv_denom = 1.0 / (a*m + b*q + c*o);
    double e1 = d*m - b*n - c*p;
    double beta = e1*inv_denom;

    if(beta < 0.0 || beta > 1,0){
        return false;
    }

    double e2 = a*n + d*q + c*r;
    double gamma = e2*inv_denom;

    if(gamma < 0.0 || gamma > 1.0){
        return false;
    }

    if(beta + gamma > 1.0){
        return false;
    }

    double e3 = a*p - b*r + d*o;
    double t_ = e3*inv_denom;

    if(t < kEpsilon){
        return false;
    }
    
    t = t_;
    s.normal = normal;
    s.local_hit_point = ray.o + t_*ray.d;
    return true;
}