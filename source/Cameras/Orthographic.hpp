#include "Camera.hpp"

class Orthographic : public Camera{
public:
    Orthographic(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));

    void set_distance(const float dist);
    float get_distance_from_vp() const;

    void render_scene(World& w);
};