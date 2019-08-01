#pragma once

#include "../Utilities/RGBColor.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Ray.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Utilities/Constants.hpp"
					
class GeometricObject {	
public:	
	GeometricObject();									// default constructor
	GeometricObject(const GeometricObject& object);		// copy constructor
	virtual GeometricObject* clone(void) const = 0;		// virtual copy constructor
	virtual ~GeometricObject ();						// destructor
		
	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const = 0; 												 

	// the following three functions are only required for Chapter 3
	void set_color(const RGBColor& c);		
	void set_color(const float r, const float g, const float b);
	RGBColor get_color(void);

	void set_material(Material* material);
	Material* get_material() const;


protected:
	RGBColor color;
	Material* material_ptr;
	GeometricObject& operator= (const GeometricObject& rhs);
};

inline void GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

inline void GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

inline RGBColor GeometricObject::get_color(void) {
	return (color);
}