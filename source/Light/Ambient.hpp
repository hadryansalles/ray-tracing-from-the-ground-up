#pragma once

#include "Light.hpp"

class Ambient: public Light {
public:
    Ambient();   							
    Ambient(const Ambient& a); 					 
    virtual Light* clone() const;	
    Ambient& operator= (const Ambient& rhs);									
    virtual ~Ambient();
            
    void scale_radiance(const float b);

    void set_color(const float c);
    void set_color(const RGBColor& c);
    void set_color(const float r, const float g, const float b); 
    
    virtual Vector3D get_direction(ShadeRec& s); 
    
    virtual RGBColor L(ShadeRec& s);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

protected:
    float		ls;
    RGBColor	color;
};