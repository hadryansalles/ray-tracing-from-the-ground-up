#include "Vector3D.hpp"
#include "Normal.hpp"
#include "Point3D.hpp"

Vector3D::Vector3D(void)
	 : x(0.0), y(0.0), z(0.0)							
{}

Vector3D::Vector3D(double a)
	 : x(a), y(a), z(a)							
{}

Vector3D::Vector3D(double _x, double _y, double _z)	 
	: x(_x), y(_y), z(_z)
{}

Vector3D::Vector3D(const Vector3D& vector)
	: x(vector.x), y(vector.y), z(vector.z)
{}

// constructs a vector from a normal
Vector3D::Vector3D(const Normal& n)	 
	: x(n.x), y(n.y), z(n.z)
{}

// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions
Vector3D::Vector3D(const Point3D& p)	 
	: x(p.x), y(p.y), z(p.z)
{}

Vector3D::~Vector3D (void) 							
{}

Vector3D& Vector3D::operator= (const Vector3D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}

// assign a Normal to a vector
Vector3D& Vector3D::operator= (const Normal& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// assign a point to a vector
Vector3D& Vector3D::operator= (const Point3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// length of the vector
double Vector3D::length(void) {
	return (sqrt(x * x + y * y + z * z));
}

// converts the vector to a unit vector
void Vector3D::normalize(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}

// converts the vector to a unit vector and returns the vector
Vector3D& Vector3D::hat(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
	return (*this);
} 

// multiplication by a matrix on the left
Vector3D operator* (const Matrix& mat, const Vector3D& v) {
	return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}

// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object
Vector3D Vector3D::operator- (void) const {
	return (Vector3D(-x, -y, -z));    
}

// the square of the length
double Vector3D::len_squared(void) {	
	return (x * x + y * y + z * z);
}

// multiplication by a double on the right
Vector3D Vector3D::operator* (const double a) const {	
	return (Vector3D(x * a, y * a, z * a));	
}

// division by a double
Vector3D Vector3D::operator/ (const double a) const {	
	return (Vector3D(x / a, y / a, z / a));	
}

// addition
Vector3D Vector3D::operator+ (const Vector3D& v) const {
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}

// subtraction
Vector3D Vector3D::operator- (const Vector3D& v) const {
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}

// dot product
double Vector3D::operator* (const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
} 

// cross product
Vector3D Vector3D::operator^ (const Vector3D& v) const {
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}

// compound addition
Vector3D& Vector3D::operator+= (const Vector3D& v) {
	x += v.x; y += v.y; z += v.z;
	return (*this);
}

// multiplication by a double on the left
Vector3D operator* (const double a, const Vector3D& v) {
	return (Vector3D(a * v.x, a * v.y, a * v.z));	
}