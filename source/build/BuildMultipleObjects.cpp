void 												
World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new MultipleObjects(this); 
	
	background_color = RGBColor(black);
	
	// use access functions to set centre and radius
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	
	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
	add_object(plane_ptr);
}
