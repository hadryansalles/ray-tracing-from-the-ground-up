#pragma once

#include "Pinhole.hpp"
#include "../World/World.hpp"

Pinhole::Pinhole(Point3D eye_p, Point3D lookat):
    Camera(eye_p, lookat),
    d(1),
    zoom(1)
{}

void Pinhole::set_distance(const float dist){
    d = dist;
}

float Pinhole::get_distance_from_vp() const{
    return d;
}

void Pinhole::set_zoom(const float zoom){
    this->zoom = zoom;
}

float Pinhole::get_zoom() const{
    return zoom;
}

void Pinhole::render_scene(World& w){
    RGBColor L;
    ViewPlane* vp = &w.vp;
    Ray ray;
    Point2D sp;
    Point2D pp;
    int depth = 0;

    w.openWindow(vp->hres, vp->vres);
    vp->s /= zoom;
    ray.o = eye;
    vp->sampler_ptr->generate_samples();
    
	// TIME MANAGER
	struct timespec start_processing;
	struct timespec start_displaying;
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &start_processing);
	float time_displaying = 0;

    for (int r = 0; r < vp->vres; r++) {	
		for (int c = 0; c <= vp->hres; c++) {					

			// PROCESSING STUFF	
			// ANTI ALIASING
			L = black;
			for(int j = 0; j < vp->num_samples; j++) {
				sp = vp->sampler_ptr->sample_unit_square();
				pp.x = vp->s*(c - 0.5*vp->hres + sp.x);
				pp.y = vp->s*(r - 0.5*vp->vres + sp.y);
				ray.d = ray_direction(pp);
				L += w.tracer_ptr->trace_ray(ray);
			}
			L /= vp->num_samples;
				
			clock_gettime(CLOCK_MONOTONIC, &start_displaying); 			
			
			// DISPLAYING STUFF
			w.display_pixel(r, c, L);
			w.window->update();
			if(!w.window->isOpen()){
				return;
			}

            // TIME MANAGER
			clock_gettime(CLOCK_MONOTONIC, &now); 			
			time_displaying += (now.tv_sec - start_displaying.tv_sec);
			time_displaying += (now.tv_nsec - start_displaying.tv_nsec)/1000000000.0;
		}	
	}
	printf("\r\nRendering completed.\nTotal processing time: %.4f seconds.\nTotal displaying time: %.4f seconds.\n", 
		(now.tv_sec - start_processing.tv_sec)+((now.tv_nsec - start_processing.tv_nsec)/1000000000.0) - time_displaying, time_displaying);
	while(w.window->isOpen()){
		w.window->update();
	}	
}

Vector3D Pinhole::ray_direction(const Point2D& pixel_point) const {
    Vector3D dir = pixel_point.x*u + pixel_point.y*v - d*w;
    dir.normalize();
    return dir;
}