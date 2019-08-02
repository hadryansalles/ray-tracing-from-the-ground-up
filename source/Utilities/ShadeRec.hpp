#pragma once

#include <vector>
#include "Point3D.hpp"
#include "Normal.hpp"
#include "Ray.hpp"
#include "RGBColor.hpp"

class Material;
class World;	// only need a forward class declaration as the World data member is a reference

class ShadeRec {
public:	
	bool hit_an_object;				// did the ray hit an object?
	Point3D	local_hit_point;		// for textures 
	Point3D hit_point; 				// world coordinates of hit point
	Normal normal;					// normal at hit point
	Material* material_ptr;			// material of nearest object
	World& w;						// world reference for shading
	Ray ray;
	int depth;
	float t;

	ShadeRec(World& wr);			// constructor
	ShadeRec(const ShadeRec& sr);	// copy constructor
	~ShadeRec();
};