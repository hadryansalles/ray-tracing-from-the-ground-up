#include "World.hpp"
#include "../Utilities/Constants.hpp"

// Window
#include "../Window/Window-THREAD.hpp"
#include "../Window/Window-NOTHREAD.hpp"

// geometric objects
#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Sphere.hpp"
#include "../GeometricObjects/Box.hpp"
#include "../GeometricObjects/Triangle.hpp"
#include "../GeometricObjects/Disk.hpp"
#include "../GeometricObjects/OpenCylinder.hpp"
#include "../GeometricObjects/Cylinder.hpp"
#include "../GeometricObjects/Grid.hpp"
#include "../GeometricObjects/SmoothMeshTriangle.hpp"
#include "../GeometricObjects/FlatMeshTriangle.hpp"

// Lights
#include "../Light/Directional.hpp"
#include "../Light/PointLight.hpp"

// Samplers
#include "../Samplers/MultiJittered.hpp"
#include "../Samplers/NRooks.hpp"

// tracers
//#include "../Tracers/MultipleObjects.hpp"
//#include "../Tracers/Sinusoid.hpp"
#include "../Tracers/RayCast.hpp"

// Cameras
#include "../Cameras/Pinhole.hpp"
#include "../Cameras/Orthographic.hpp"
#include "../Cameras/ThinLens.hpp"

// Materials
#include "../Materials/Matte.hpp"

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Maths.hpp"

// build functions
//#include "../build/BuildSingleSphere.hpp"
//#include "../build/BuildSpheresQueue.hpp"
//#include "../build/BuildSingleSphereLight.hpp"
//#include "../build/BuildShadedTest.hpp"
//#include "../build/BuildBox.hpp"
#include "../build/BuildSphereGrid.hpp"
//#include "../build/BuildSimpleMesh.hpp"
//#include "../build/BuildBBCoverPic.hpp"
//#include "../build/BuildBBCoverPicLight.hpp"
//#include "../build/BuildMultipleObjects.hpp"
//#include "../build/BuildSinusoid.hpp"
//#include "../build/BuildHorizontalPlane.hpp"

World::World()
	:  	background_color(black),
		tracer_ptr(NULL),
		window(NULL),
		camera(new Orthographic()),
		ambient_ptr(new Ambient())
{}

World::~World() {		
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}	
	if(window){
		delete window;
		window = NULL;
	}
	if(camera){
		delete camera;
		camera = NULL;
	}
	if(ambient_ptr){
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	delete_objects();
}

RGBColor World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}

// Set color to red if any component is greater than one
RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function
void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

   window->setPixel(x, y, (int)(mapped_color.r * 255),
                          (int)(mapped_color.g * 255),
                          (int)(mapped_color.b * 255));
}

ShadeRec World::hit_objects(const Ray& ray, const float tmin_) {

	ShadeRec sr(*this); 
	Normal normal;
	Point3D local_hit_point; 			
	
	float t;
	
	float tmin = tmin_;
	int num_objects = objects.size();
		
	for (int j = 0; j < num_objects; j++) {

    	if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t; 
			//sr.color= objects[j]->get_color();
			sr.material_ptr = objects[j]->get_material();
			sr.hit_point = ray.o + t*ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point; 
		}
	}
	
	if(sr.hit_an_object){
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}		

	return (sr);   
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 
void World::delete_objects() {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

void World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}

void World::add_light(Light* light_ptr){
	lights.push_back(light_ptr);
}

void World::openWindow(int w, int h, bool thread) {
	if(thread){
		window = new Window_THREAD(w, h);
	}
	else{
		window = new Window_NOTHREAD(w, h);
	}
	window->init();
}

void World::set_camera(Camera* cam_pt){
	if(camera){
		delete camera;
	}
	camera = cam_pt;
}

void World::set_ambient_light(Light* light_ptr){
	if(ambient_ptr){
		delete ambient_ptr;
	}
	ambient_ptr = light_ptr;
}