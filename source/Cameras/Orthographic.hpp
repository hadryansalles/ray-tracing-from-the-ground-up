#pragma once

#include "Camera.hpp"

class Orthographic : public Camera{
public:
    Orthographic(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));
    void render_scene(World& w);
};