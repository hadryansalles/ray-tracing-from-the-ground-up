#pragma once

#include "GeometricObject.hpp"

class Plane: public GeometricObject {
	
public:
	Plane();   												// default constructor
	Plane(const Point3D& point, const Normal& normal);		// constructor	
	Plane(const Plane& plane); 								// copy constructor

	virtual GeometricObject* clone(void) const;				// virtual copy constructor
	Plane& operator= (const Plane& rhs);					// assignment operator
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	
private:
	Point3D a;   				// point through which plane passes 
	Normal n;					// normal to the plane
	
	static const double kEpsilon;   // for shadows and secondary rays
};