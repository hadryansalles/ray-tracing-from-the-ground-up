#pragma once

#include <math.h>
#include "Matrix.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

class Normal {	
public:	
	double	x, y, z;
				
public:	
	Normal();											// default constructor
	Normal(double a);									// constructor
	Normal(double _x, double _y, double _z);			// constructor
	Normal(const Normal& n); 							// copy constructor
	Normal(const Vector3D& v);							// constructs a normal from vector
	~Normal(void);										// destructor

	Normal& operator= (const Normal& rhs); 				// assignment operator
	Normal& operator= (const Vector3D& rhs); 			// assignment of a vector to a normal
	Normal& operator= (const Point3D& rhs);				// assignment of a point to a normal
	Normal operator- (void) const;						// unary minus
	Normal operator+ (const Normal& n) const;			// addition
	Normal& operator+= (const Normal& n);				// compound addition
	double operator* (const Vector3D& v) const;			// dot product with a vector on the right
	Normal operator* (const double a) const;			// multiplication by a double on the right			
	void normalize(void); 								// convert normal to a unit normal
};