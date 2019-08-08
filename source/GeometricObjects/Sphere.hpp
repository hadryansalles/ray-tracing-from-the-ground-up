#pragma once

#include "GeometricObject.hpp"

class Sphere: public GeometricObject {	
private:
	Point3D center;   				// center coordinates as a point  
	double radius;					// the radius 
	
	static const double kEpsilon;   // for shadows and secondary rays						

public:
	Sphere(void);   									// Default constructor			
	Sphere(Point3D center, double r);					// Constructor 
	Sphere(const Sphere& sphere); 						// Copy constructor
	virtual GeometricObject* clone(void) const;			// Virtual copy constructor

	Sphere& operator= (const Sphere& sphere);			// assignment operator
																				
	void set_center(const Point3D& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);

	virtual BBox get_bounding_box() const;
		
	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;	
	virtual bool shadow_hit(const Ray& ray, float& tmin) const;
};