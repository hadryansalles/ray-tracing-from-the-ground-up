#pragma once

#include "Matrix.hpp"
#include <math.h>

class Point2D {
public:
    double x, y;

    Point2D();
    Point2D(const double a);
    Point2D(const double a, const double b);
    Point2D(const Point2D &p);
    ~Point2D();
    
	Point2D& operator= (const Point2D& p);						// assignment operator	
	Point2D operator- (void) const;								// unary minus
	Point2D operator* (const double a) const;					// multiplication by a double on the right

	double d_squared(const Point2D& p) const;					// square of distance bertween two points
	double distance(const Point2D& p) const;					// distance bewteen two points
};

Point2D operator* (double a, const Point2D& p);