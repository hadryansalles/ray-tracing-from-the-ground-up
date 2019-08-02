#pragma once

#include "Light.hpp"

class Ambient:public Light{
public:
    Ambient(float ls_ = 1.0, RGBColor color_ = 1.0, bool shadows_ = false);
    Ambient(const Ambient& ambient);

    virtual Light* clone() const;
    Ambient& operator=(const Ambient& rhs);

    float get_ls() const;
    void set_ls(const float ls_);

    RGBColor get_color() const;
    void set_color(const RGBColor color_);

    virtual Vector3D get_direction(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);

protected:
    float ls;
    RGBColor color;
};