#pragma once 

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Ray {
public:	
	Point3D	o;  		// origin 
	Vector3D d; 		// direction 
	
	Ray();			
	Ray(const Point3D& origin, const Vector3D& dir);	
	Ray(const Ray& ray); 		
	~Ray(void);

	Ray& operator= (const Ray& rhs);								
};