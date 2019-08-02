#pragma once

#include "Ambient.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"

#include "../World/World.hpp"
#include "../Utilities/ShadeRec.hpp"

class Directional : public Ambient{
public:
    Directional(Vector3D dir_ = Vector3D(0, 1, 0), const float ls_ = 1.0, const RGBColor color_ = RGBColor(1), bool shadows_ = false);
    Directional(const Directional& dl);
    virtual Light* clone() const;
    Directional& operator=(const Directional& rhs);

    void set_direction(Vector3D d);
    Vector3D get_direction(ShadeRec& sr);   

    virtual RGBColor L(ShadeRec& sr);

protected:
    Vector3D dir;
};