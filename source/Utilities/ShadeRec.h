#ifndef __SHADE_REC__
#define __SHADE_REC__

// this file contains the declaration of the class ShadeRec

class World;	// only need a forward class declaration as the World data member is a reference

#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"

class ShadeRec {
	public:
	
		bool				hit_an_object;		// did the ray hit an object?
		Point3D				local_hit_point;	// world coordinates of hit point 
		Normal				normal;				// normal at hit point
		RGBColor			color;				// used in Chapter 3 only
		World&				w;					// world reference for shading
				
		ShadeRec(World& wr);				// constructor
		
		ShadeRec(const ShadeRec& sr);		// copy constructor
};

#endif
