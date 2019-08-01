#pragma once

// The World class does not have a copy constructor or an assignment operator, for the followign reasons:
// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include <vector>
#include "ViewPlane.hpp"

// Window
#include "../Window/Window-THREAD.hpp"
#include "../Window/Window-NOTHREAD.hpp"

// geometric objects
#include "../GeometricObjects/GeometricObject.hpp"
#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Sphere.hpp"

// Lights
#include "../Light/Light.hpp"
#include "../Light/Ambient.hpp"
#include "../Light/PointLight.hpp"

// tracers
#include "../Tracers/Tracer.hpp"
#include "../Tracers/MultipleObjects.hpp"
#include "../Tracers/Sinusoid.hpp"
#include "../Tracers/RayCast.hpp"

// Cameras
#include "../Cameras/Camera.hpp"
#include "../Cameras/Pinhole.hpp"
#include "../Cameras/Orthographic.hpp"
#include "../Cameras/ThinLens.hpp"

// Materials
#include "../Materials/Matte.hpp"

// utilities
#include "../Utilities/Ray.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Utilities/Maths.hpp"
#include "../Utilities/Constants.hpp"
#include "../Utilities/RGBColor.hpp"

// build functions
//#include "../build/BuildSingleSphere.hpp"
//#include "../build/BuildSpheresQueue.hpp"
//#include "../build/BuildBBCoverPic.hpp"
#include "../build/BuildBBCoverPicLight.hpp"
//#include "../build/BuildMultipleObjects.hpp"
//#include "../build/BuildSinusoid.hpp"
//#include "../build/BuildHorizontalPlane.hpp"


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

	void openWindow(int w, int h, bool thread = true);
					
private:
	void delete_objects();
};