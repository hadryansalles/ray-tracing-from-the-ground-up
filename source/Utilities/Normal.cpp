#include "Normal.hpp"

Normal::Normal(void)
	 : x(0.0), y(0.0), z(0.0) 
{}

Normal::Normal(double a)
	 : x(a), y(a), z(a)							
{}

Normal::Normal(double _x, double _y, double _z)	 
	: x(_x), y(_y), z(_z)
{}

Normal::Normal(const Normal& n)
	: x(n.x), y(n.y), z(n.z)
{}

// construct a normal from a vector
Normal::Normal(const Vector3D& v)	 
	: x(v.x), y(v.y), z(v.z)  
{}

Normal::~Normal (void) 							
{}

// assignment operator
Normal& Normal::operator= (const Normal& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}

// assignment of a vector to a normal
Normal& Normal::operator= (const Vector3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// assignment of a point to a normal
Normal& Normal::operator= (const Point3D& rhs) {		
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

void Normal::normalize(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}

// multiplication by a matrix on the left
// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix
Normal 	operator* (const Matrix& mat, const Normal& n) {
	return (Normal(	mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
					mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
					mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));
}

// unary minus
Normal Normal::operator- (void) const {
	return (Normal(-x, -y, -z));
}
// addition of two normals
Normal Normal::operator+ (const Normal& n) const {
	return (Normal(x + n.x, y + n.y, z + n.z));
}
// compound addition of two normals
Normal& Normal::operator+= (const Normal& n) {
	x += n.x; y += n.y; z += n.z;
    return (*this);
}
// dot product of a normal on the left and a vector on the right
double Normal::operator* (const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
}
// multiplication by a double on the right
Normal Normal::operator* (const double a) const {
	return (Normal(x * a, y * a, z * a));
}
// multiplication by a double on the left
Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.x, f * n.y,f * n.z));
}
// addition of a vector on the left to return a vector 
Vector3D operator+ (const Vector3D& v, const Normal& n) {	
	return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}	
// subtraction of a normal from a vector to return a vector
Vector3D operator- (const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}
// dot product of a vector on the left and a normal on the right
double operator* (const Vector3D& v, const Normal& n) {
	return (v.x * n.x + v.y * n.y + v.z * n.z);     
}