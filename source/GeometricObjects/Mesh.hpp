#pragma once

#include "../Utilities/Normal.hpp"
#include "../Utilities/Point3D.hpp"
#include <vector>

class Mesh {
public:
    std::vector<Point3D> vertices;
    std::vector<int> indices;
    std::vector<Normal> normals;
    std::vector<std::vector<int>>vertex_faces; // faces shared by each vertex
    std::vector<float> u; // texture coordinate
    std::vector<float> v;
    int num_vertices;
    int num_triangles;

    Mesh();
    Mesh(const Mesh& mesh);
    Mesh& operator=(const Mesh& rhs);
    Mesh* clone() const;
    ~Mesh();
};