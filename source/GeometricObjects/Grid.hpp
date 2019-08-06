#pragma once

#include "Compound.hpp"
#include "Mesh.hpp"

class Grid : public Compound {
public:
    Grid();
    Grid(BBox bbox_, int nx_, int ny_, int nz_);
    Grid(Mesh* mesh_ptr_);
    Grid(const Grid& grid);
    
    Grid& operator=(const Grid& rhs);
    Grid* clone() const;

    virtual BBox get_bounding_box() const;
    void set_bouding_box(const BBox bbox_);

    void set_number_cells(const int nx_, const int ny_, const int nz_);
    void setup_cells();
 
    //void read_flat_triangles(char* file_name);
    //void read_smooth_triangles(char* file_name);

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

protected:
    std::vector<GeometricObject*> cells;
    BBox bbox;
    Mesh* mesh_ptr;
    bool reverse_normal;
    int nx;
    int ny;
    int nz;

    Point3D min_coordinates();
    Point3D max_coordinates();
    //void read_ply_file(char* file_name, const int triangle_type);
    //void compute_mesh_normals();
};