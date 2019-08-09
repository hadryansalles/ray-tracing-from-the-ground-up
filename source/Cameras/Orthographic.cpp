#include "Orthographic.hpp"
#include "../World/World.hpp"

Orthographic::Orthographic(Point3D eye, Point3D lookat):
    Camera(eye, lookat)
{}

void Orthographic::render_scene(World& w){
    RGBColor	pixel_color;	 	
	Ray			ray;					
	ViewPlane* vp = &w.vp;
    float		zw		= 100;			// hardwired in
	Point2D sp; // sample point in a square
	Point2D pp; // sample point pixel
	int depth = 0;
	ray.d = Vector3D(0, 0, -1);

	w.openWindow(vp->vres, vp->hres);

	// TIME MANAGER
	struct timespec start_processing;
	struct timespec start_displaying;
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &start_processing);

	float time_displaying = 0;
	
	for (int r = 0; r < vp->vres; r++) {			// up
		for (int c = 0; c <= vp->hres; c++) {		// across 					

			// PROCESSING STUFF	
			// ANTI ALIASING
			pixel_color = black;
			for(int j = 0; j < vp->num_samples; j++) {
				sp = vp->sampler_ptr->sample_unit_square();
				pp.x = vp->s*(c - 0.5*vp->hres + sp.x);
				pp.y = vp->s*(r - 0.5*vp->vres + sp.y);
				ray.o = Point3D(pp.x, pp.y, zw);
				pixel_color += w.tracer_ptr->trace_ray(ray, depth);
			}
			pixel_color /= vp->num_samples;
				
			clock_gettime(CLOCK_MONOTONIC, &start_displaying); 			
			
			// DISPLAYING STUFF
			w.display_pixel(r, c, pixel_color);
			w.window->update();
			if(!w.window->isOpen()){
				return;
			}
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