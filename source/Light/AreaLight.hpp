#pragma once 

#include "Light.hpp"
#include "../Materials/Material.hpp"
#include "../GeometricObjects/GeometricObject.hpp"

class AreaLight : public Light {
public:
    AreaLight();
    AreaLight(const AreaLight& alight);
    ~AreaLight();
    AreaLight& operator=(const AreaLight& rhs);
    AreaLight* clone() const;

    virtual Vector3D get_direction(ShadeRec& sr);
    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
    virtual RGBColor L(ShadeRec& sr);
    
    virtual float G(const ShadeRec& sr) const;
    virtual float pdf(const ShadeRec& sr) const;

    void set_object(GeometricObject* object);

private:
    GeometricObject* object_ptr;
    Material* material_ptr;
    Point3D sample_point;
    Normal light_normal;
    Vector3D wi;    
};