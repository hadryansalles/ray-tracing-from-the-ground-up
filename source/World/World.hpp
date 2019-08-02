#pragma once

// The World class does not have a copy constructor or an assignment operator, for the followign reasons:
// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include <vector>

#include "ViewPlane.hpp"
#include "../Utilities/RGBColor.hpp"
#include "../Tracers/Tracer.hpp"
#include "../GeometricObjects/GeometricObject.hpp"
#include "../Utilities/Ray.hpp"

#include "../Window/Window.hpp"

#include "../Cameras/Camera.hpp"
#include "../Light/Light.hpp"
#include "../Light/Ambient.hpp"

class World {	
public:
	ViewPlane vp;
	RGBColor background_color;

	Tracer* tracer_ptr;
	Window* window;
	Camera* camera;
	Light* ambient_ptr;

	std::vector<GeometricObject*> objects;		
	std::vector<Light*> lights;

public:
	World();												
	~World();
							
	void add_object(GeometricObject* object_ptr);
	void add_light(Light* light_ptr);
	
	void build();
				
	RGBColor max_to_one(const RGBColor& c) const;
	RGBColor clamp_to_color(const RGBColor& c) const;
	
	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;
	ShadeRec hit_objects(const Ray& ray, const float tmin_ = kHugeValue);

	void set_camera(Camera* cam_pt);
	void openWindow(int w, int h, bool thread = true);

	void set_ambient_light(Light* light_ptr);

private:
	void delete_objects();
};