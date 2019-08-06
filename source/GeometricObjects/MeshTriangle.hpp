#pragma once

#include "GeometricObject.hpp"
#include "../Utilities/Maths.hpp"
#include "Mesh.hpp"

class MeshTriangle : public GeometricObject {
public:
    MeshTriangle(Mesh* mesh_ptr_ = NULL, const int i0 = 0, const int i1 = 0, const int i2 = 0);
    MeshTriangle(const MeshTriangle& mesh_triangle);
    MeshTriangle& operator=(const MeshTriangle& rhs);
    virtual MeshTriangle* clone() const = 0;
    virtual ~MeshTriangle();

    void set_mesh_ptr(Mesh* mesh_ptr_);
    Mesh* get_mesh_ptr() const;

    void compute_normal(const bool reverse_normal);

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const = 0;

    virtual Normal get_normal() const;
    virtual BBox get_bounding_box() const;

protected:
    Mesh* mesh_ptr;
    int index0;
    int index1;
    int index2;
    Normal normal;

    float interpolate_u(const float beta, const float gamma) const;
    float interpolate_v(const float beta, const float gamma) const;
};