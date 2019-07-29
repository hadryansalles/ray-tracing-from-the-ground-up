#pragma once

#include "Point3D.hpp"
#include "Normal.hpp"
#include "RGBColor.hpp"
#include "Constants.hpp"

class World;	// only need a forward class declaration as the World data member is a reference

class ShadeRec {
public:	
	bool hit_an_object;				// did the ray hit an object?
	Point3D	local_hit_point;		// world coordinates of hit point 
	Normal normal;					// normal at hit point
	RGBColor color;					// used in Chapter 3 only
	World& w;						// world reference for shading
			
	ShadeRec(World& wr);			// constructor
	ShadeRec(const ShadeRec& sr);	// copy constructor
};