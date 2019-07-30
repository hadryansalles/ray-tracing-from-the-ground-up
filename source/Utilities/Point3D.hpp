#pragma once 

#include <math.h>
#include "Matrix.hpp"
#include "Vector3D.hpp"

class Point3D {
public:
	double x, y, z;
	
	Point3D();													// default constructor
	Point3D(const double a);									// constructor
	Point3D(const double a, const double b, const double c);	// constructor
	Point3D(const Point3D& p);									// copy constructor
	~Point3D();													// destructor
	
	Point3D& operator= (const Point3D& p);						// assignment operator	
	Point3D operator- (void) const;								// unary minus
	Vector3D operator- (const Point3D& p) const;				// vector joining two points
	Point3D operator+ (const Vector3D& v) const;				// addition of a vector				
	Point3D operator- (const Vector3D& v) const;				// subtraction of a vector
	Point3D operator* (const double a) const;					// multiplication by a double on the right

	double d_squared(const Point3D& p) const;					// square of distance bertween two points
	double distance(const Point3D& p) const;					// distance bewteen two points
};

Point3D operator* (const Matrix& mat, const Point3D& p);
Point3D operator* (double a, const Point3D& p);