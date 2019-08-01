#include "Pinhole.hpp"
#include "../Samplers/Jittered.hpp"

class ThinLens: public Pinhole {
public:
    ThinLens(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));
    ~ThinLens();

    void render_scene(World& w);

    void set_sampler(Sampler* sp);
    Sampler* get_sampler();

    void set_lens_radius(const float l_r);
    float get_lens_radius();

    void set_focal_dist(const float focal_d);
    float get_focal_dist();

private:
    float lens_radius;
    float f; // Focal plane distance
    Sampler* sampler_ptr;

    Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point = Point2D(0, 0)) const;
};