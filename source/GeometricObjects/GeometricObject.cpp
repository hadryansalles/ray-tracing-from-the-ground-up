// this file contains the definition of the class GeometricObject 

#include "Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
	: 	color(black)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object)
	: 	color(object.color)
{}	


// ---------------------------------------------------------------------- assignment operator

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	
	if (this == &rhs)
		return (*this);
		
	color = rhs.color;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {}
