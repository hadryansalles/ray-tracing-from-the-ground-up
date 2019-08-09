#pragma once

#include "Ambient.hpp"

class PointLight: public Ambient{
public:
    PointLight(Vector3D location = Vector3D(0), float ls_ = 1.0, RGBColor color_ = 1.0, bool shadows_ = false);
    PointLight(PointLight& point);

    Vector3D get_location() const;
    void set_location(const Vector3D location_);
    void set_location(const float x, const float y, const float z);

    Vector3D get_direction(ShadeRec& sr);
    RGBColor L(ShadeRec& sr);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
    Vector3D location;
};