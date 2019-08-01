#pragma once

#include "../Utilities/RGBColor.hpp"
#include "../Utilities/ShadeRec.hpp"

class Material{
public:
    Material();
    Material(Material& material);
    virtual ~Material();

    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor path_shade(ShadeRec& sr);
};