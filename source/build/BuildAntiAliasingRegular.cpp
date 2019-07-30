void World::build(void) {
    vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1);
	vp.set_gamma(1.0);
	vp.set_num_samples(16);
	
	background_color = black;
	tracer_ptr = new MultipleObjects(this); 
	Sphere* sphere_pt = new Sphere();
	sphere_pt->set_center(-200, 100, 0);
	sphere_pt->set_radius(300);
	sphere_pt->set_color(1, 0, 0);
	add_object(dynamic_cast <GeometricObject*> (sphere_pt));
}