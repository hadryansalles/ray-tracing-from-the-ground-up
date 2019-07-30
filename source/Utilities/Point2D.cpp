#include "Point2D.hpp"

Point2D::Point2D()
	:x(0), y(0)
{}

Point2D::Point2D(const double a)
	:x(a), y(a)
{}

Point2D::Point2D(const double a, const double b)
	:x(a), y(b)
{}

Point2D::Point2D(const Point2D& p)
	:x(p.x), y(p.y)
{}

Point2D::~Point2D() 
{}

Point2D& Point2D::operator= (const Point2D& rhs) {
	
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; 

	return (*this);
}

// distance between two points
double Point2D::distance(const Point2D& p) const {
	return (sqrt(		(x - p.x) * (x - p.x) 
					+ 	(y - p.y) * (y - p.y)));
}

// unary minus
Point2D Point2D::operator- (void) const {
	return (Point2D(-x, -y));
}

// mutliplication by a double on the right
Point2D Point2D::operator* (const double a) const {
	return (Point2D(x * a,y * a));
}

// the square of the distance between the two points as a member function
double Point2D::d_squared(const Point2D& p) const {
	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y) );
}

// multiplication by a double on the left
Point2D operator* (double a, const Point2D& p) {
	return (Point2D(a * p.x, a * p.y));
}
