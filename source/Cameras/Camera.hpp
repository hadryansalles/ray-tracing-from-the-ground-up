#pragma once

#include "../Utilities/Point3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Vector3D.hpp"

class World;

class Camera{
protected:
    Point3D eye;
    Point3D look_at;
    Vector3D up;
    Vector3D u, v, w;
    float exposure_time;

public:
    Camera(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));
    virtual ~Camera();

    void compute_uvw();
    
    virtual void render_scene(World& w) = 0;

    void set_eye(const Point3D eye_p);
    void set_eye(const float x, const float y, const float z);
    Point3D get_eye() const;
    
    void set_lookat(const Point3D lookat);
    void set_lookat(const float x, const float y, const float z);
    Point3D get_lookat() const;

    void set_up(const Vector3D up_d);
    Vector3D get_up() const;

    void set_exposure_time(const float exposure_t);
    float get_exposure_time() const;
};