#pragma once

#include "../Light/Light.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"

#include "../World/World.hpp"			
#include "../Utilities/ShadeRec.hpp"

class Directional: public Light {
public:
    Directional(void);   							
    Directional(const Directional& dl); 
    virtual Light* clone(void) const;			
    Directional& operator= (const Directional& rhs); 
    virtual	~Directional(void); 
            
    void scale_radiance(const float b);
    void set_color(const float c);
    void set_color(const RGBColor& c);
    void set_color(const float r, const float g, const float b); 		
    void set_direction(Vector3D d);						
    void set_direction(float dx, float dy, float dz);
    virtual Vector3D get_direction(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);	
    
private:
    float		ls;			
    RGBColor	color;
    Vector3D	dir;		// direction the light comes from
};