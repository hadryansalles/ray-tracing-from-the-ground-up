#pragma once

#include "Light.hpp"

class Ambient:public Light{
public:
    Ambient(float ls_ = 1.0, RGBColor color_ = 1.0, bool shadows_ = false);
    Ambient(Ambient& ambient);

    float get_ls() const;
    void set_ls(const float ls_);

    RGBColor get_color() const;
    void set_color(const RGBColor color_);

    Vector3D get_direction(ShadeRec& sr);
    RGBColor L(ShadeRec& sr);

private:
    float ls;
    RGBColor color;
};