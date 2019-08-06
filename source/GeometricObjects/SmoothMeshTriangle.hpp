#pragma once

#include "MeshTriangle.hpp"

class SmoothMeshTriangle : public MeshTriangle {
public:
    SmoothMeshTriangle(Mesh* mesh_ptr_ = NULL, const int i0 = 0, const int i1 = 0, const int i2 = 0);
    SmoothMeshTriangle(const SmoothMeshTriangle& flat_mesh);
    SmoothMeshTriangle& operator=(const SmoothMeshTriangle& rhs);
    virtual SmoothMeshTriangle* clone() const;
    virtual ~SmoothMeshTriangle();
    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

protected:
    Normal interpolate_normal(const float beta, const float gamma) const;

};