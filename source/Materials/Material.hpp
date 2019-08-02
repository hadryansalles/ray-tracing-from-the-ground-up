#pragma once
    
#include "../World/World.hpp"   
#include "../Utilities/RGBColor.hpp"
#include "../Utilities/ShadeRec.hpp"

class Material{
public:
    Material();
    Material(const Material& material);
    virtual Material* clone(void) const = 0;
    virtual ~Material();

    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor path_shade(ShadeRec& sr);

    Material& operator= (const Material& rhs);
};