#pragma once

#include "../Utilities/Point3D.hpp"
#include "../Utilities/Ray.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../GeometricObjects/BBox.hpp"
					
class GeometricObject {	
public:	
	GeometricObject(Material* material_p = NULL);
	GeometricObject(const GeometricObject& object);		// copy constructor
	virtual GeometricObject* clone(void) const = 0;		// virtual copy constructor
	virtual ~GeometricObject ();						// destructor
		
	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const = 0; 												 

	virtual void set_material(Material* material_p);
	Material* get_material() const;

	virtual BBox get_bounding_box();

protected:
	mutable Material* material_ptr;
	GeometricObject& operator= (const GeometricObject& rhs);
};