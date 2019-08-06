#pragma once

#include "MeshTriangle.hpp"

class FlatMeshTriangle : public MeshTriangle {
public:
    FlatMeshTriangle(Mesh* mesh_ptr_ = NULL, const int i0 = 0, const int i1 = 0, const int i2 = 0);
    FlatMeshTriangle(const FlatMeshTriangle& flat_mesh);
    FlatMeshTriangle& operator=(const FlatMeshTriangle& rhs);
    virtual FlatMeshTriangle* clone() const;
    virtual ~FlatMeshTriangle();
    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;
};