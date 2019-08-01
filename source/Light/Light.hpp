#pragma once

#include "../Utilities/RGBColor.hpp"
#include "../Utilities/ShadeRec.hpp"


class Light{
public:
    Light(const bool shadows_ = false);
    Light(Light& light);
    virtual ~Light();

    bool get_shadows() const;
    void set_shadows(const bool shadows_);

    virtual Vector3D get_direction(ShadeRec& sr) = 0;
    virtual RGBColor L(ShadeRec& sr) = 0;

protected:
    bool shadows;
};