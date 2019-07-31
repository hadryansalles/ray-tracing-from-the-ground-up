void World::build(){
    vp.set_hres(800);
	vp.set_vres(800);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new MultipleObjects(this); 
	
	background_color = RGBColor(1);
	

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, -0.00000001));
	plane_ptr->set_color(1, 0.0, 0.0);
	add_object(plane_ptr);

	Sphere* sphere_ptr = new Sphere(Point3D(0, 0, -100), 100);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
}