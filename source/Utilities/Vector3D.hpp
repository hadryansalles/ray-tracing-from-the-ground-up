#pragma once

#include <math.h>
#include "Matrix.hpp"

class Normal;
class Point3D;

class Vector3D {
public:
	double	x, y, z;

public:
	Vector3D();											// default constructor
	Vector3D(double a);									// constructor
	Vector3D(double _x, double _y, double _z);			// constructor
	Vector3D(const Vector3D& v);						// copy constructor
	Vector3D(const Normal& n);							// constructs a vector from a Normal
	Vector3D(const Point3D& p);							// constructs a vector from a point
	~Vector3D (void);									// destructor

	Vector3D& operator= (const Vector3D& rhs);			// assignment operator
	Vector3D& operator= (const Normal& rhs); 			// assign a Normal to a vector
	Vector3D& operator= (const Point3D& rhs);  			// assign a Point3D to a vector
	Vector3D operator- (void) const;					// unary minus
			
	double length(void);								// length
	double len_squared(void);							// square of the length

	Vector3D operator* (const double a) const;			// multiplication by a double on the right			
	Vector3D operator/ (const double a) const;			// division by a double
	Vector3D operator+ (const Vector3D& v) const;	 	// addition
	Vector3D& operator+= (const Vector3D& v);			// compound addition
	Vector3D operator- (const Vector3D& v) const;		// subtraction
	double operator* (const Vector3D& b) const;			// dot product							
	Vector3D operator^ (const Vector3D& v) const;		// cross product				
	void normalize(void); 								// convert vector to a unit vector

	Vector3D& hat(void);								// return a unit vector, and normalize the vector												
};

Vector3D operator* (const double a, const Vector3D& v);
Vector3D operator* (const Matrix& mat, const Vector3D& v);