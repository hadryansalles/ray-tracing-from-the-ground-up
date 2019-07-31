#pragma once

#include "Camera.hpp"

class Pinhole : public Camera {
public:
    Pinhole(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));

    void set_distance(const float dist);
    float get_distance_from_vp() const;

    void set_zoom(const float zoom);
    float get_zoom() const;

    void render_scene(World& w);

private:
    float d; // Distance from view-plane
    float zoom; // Zoom factor

    Vector3D ray_direction(const Point2D& p) const;
};