void World::build(){
    vp.set_hres(800);
	vp.set_vres(800);
	vp.set_pixel_size(1.0);

	Pinhole* pinhole_ptr = new Pinhole(Point3D(0, 50, 100), Point3D(0, 0, -500));
	pinhole_ptr->set_distance(400);
	pinhole_ptr->set_up(Vector3D(1, 1, 0));
	pinhole_ptr->compute_uvw();
	camera = pinhole_ptr;

	tracer_ptr = new MultipleObjects(this); 
	
	background_color = RGBColor(1);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_color(1, 0.0, 0.0);
	add_object(plane_ptr);

	Sphere* sphere_ptr = new Sphere(Point3D(0, 0, 0), 20);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
}