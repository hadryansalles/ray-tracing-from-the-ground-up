// this file contains the definition of the class ShadeRec

// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "Constants.h"
#include "ShadeRec.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(World& wr)
	: 	hit_an_object(false),
		local_hit_point(),
		normal(),
		color(black),
		w(wr)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit_an_object(sr.hit_an_object),
		local_hit_point(sr.local_hit_point),
		color(sr.color),
		w(sr.w)
{}



		
		
						
		
