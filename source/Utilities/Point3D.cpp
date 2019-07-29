#include "Point3D.hpp"

Point3D::Point3D()
	:x(0), y(0), z(0)
{}

Point3D::Point3D(const double a)
	:x(a), y(a), z(a)
{}

Point3D::Point3D(const double a, const double b, const double c)
	:x(a), y(b), z(c)
{}

Point3D::Point3D(const Point3D& p)
	:x(p.x), y(p.y), z(p.z)
{}

Point3D::~Point3D() 
{}

Point3D& Point3D::operator= (const Point3D& rhs) {
	
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}

// distance between two points
double Point3D::distance(const Point3D& p) const {
	return (sqrt(		(x - p.x) * (x - p.x) 
					+ 	(y - p.y) * (y - p.y)
					+	(z - p.z) * (z - p.z) ));
}

// multiplication by a matrix on the left
Point3D operator* (const Matrix& mat, const Point3D& p) {
	return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
					mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
					mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}

// unary minus
Point3D Point3D::operator- (void) const {
	return (Point3D(-x, -y, -z));
}
// the vector that joins two points
Vector3D Point3D::operator- (const Point3D& p) const {
	return (Vector3D(x - p.x,y - p.y,z - p.z));
}
// addition of a vector to a point that returns a new point
Point3D Point3D::operator+ (const Vector3D& v) const {
	return (Point3D(x + v.x, y + v.y, z + v.z));
}
// subtraction of a vector from a point that returns a new point
Point3D Point3D::operator- (const Vector3D& v) const {
	return (Point3D(x - v.x, y - v.y, z - v.z));
}
// mutliplication by a double on the right
Point3D Point3D::operator* (const double a) const {
	return (Point3D(x * a,y * a,z * a));
}

// the square of the distance between the two points as a member function
double Point3D::d_squared(const Point3D& p) const {
	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y)
			+	(z - p.z) * (z - p.z) );
}

// multiplication by a double on the left
Point3D operator* (double a, const Point3D& p) {
	return (Point3D(a * p.x, a * p.y, a * p.z));
}
