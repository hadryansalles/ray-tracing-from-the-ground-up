#include "ShadeRec.hpp"
#include "Constants.hpp"

// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

// ------------------------------------------------------------------ constructor
ShadeRec::ShadeRec(World& wr)
	: 	hit_an_object(false),
		local_hit_point(),
		hit_point(),
		material_ptr(NULL),
		normal(),
		w(wr),
		ray(),
		depth(0),
		t(0)
{}

// ------------------------------------------------------------------ copy constructor
ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit_an_object(sr.hit_an_object),
		local_hit_point(sr.local_hit_point),
		hit_point(sr.hit_point),
		material_ptr(sr.material_ptr),
		w(sr.w),
		ray(sr.ray),
		depth(sr.depth),
		t(sr.t)
{}

ShadeRec::~ShadeRec(){
}