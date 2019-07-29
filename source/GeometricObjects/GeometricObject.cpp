#include "GeometricObject.hpp"

GeometricObject::GeometricObject(void)
	: 	color(black)
{}

GeometricObject::GeometricObject (const GeometricObject& object)
	: 	color(object.color)
{}	

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	//TODO: REMOVE AFTER CHAPTER 3	
	color = rhs.color;

	return (*this);
}

GeometricObject::~GeometricObject (void) {}
