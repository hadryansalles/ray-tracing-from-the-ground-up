#include "Mesh.hpp"

Mesh::Mesh()
    : num_vertices(0)
    , num_triangles(0) 
{}

Mesh::Mesh(const Mesh& mesh)
    : vertices(mesh.vertices)
    , indices(mesh.indices)
    , normals(mesh.normals)
    , vertex_faces(mesh.vertex_faces)
    , u(mesh.u)
    , v(mesh.v)
    , num_vertices(mesh.num_vertices)
    , num_triangles(mesh.num_triangles)
{}

Mesh& Mesh::operator=(const Mesh& rhs){
    if(this == &rhs){
        return(*this);
    }
    vertices.clear();
    indices.clear();
    normals.clear();
    vertex_faces.clear();
    u.clear();
    v.clear();

    vertices = rhs.vertices;
    indices = rhs.indices;
    normals = rhs.normals;
    vertex_faces = rhs.vertex_faces;
    u = rhs.u;
    v = rhs.v;
    num_vertices = rhs.num_vertices;
    num_triangles = rhs.num_triangles;

    return(*this);
}

Mesh* Mesh::clone() const{
    return (new Mesh(*this));
}

Mesh::~Mesh(){
    vertices.clear();
    indices.clear();
    normals.clear();
    vertex_faces.clear();
    u.clear();
    v.clear();
    num_vertices = 0;
    num_triangles = 0;
}

