#pragma once

#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"
#include "../Utilities/Ray.hpp"

class ShadeRec;

class Light{
public:
    Light(const bool shadows_ = false);
    Light(const Light& light);
    Light& operator=(const Light& rhs);
    virtual Light* clone() const = 0;
    virtual ~Light();

    bool get_shadows() const;
    void set_shadows(const bool shadows_);

    virtual Vector3D get_direction(ShadeRec& sr) = 0;
    virtual RGBColor L(ShadeRec& sr) = 0;

protected:
    bool shadows;
};