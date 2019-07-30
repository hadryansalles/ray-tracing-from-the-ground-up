void World::build(void) {
    vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	
	background_color = black;
	tracer_ptr = new MultipleObjects(this); 
	Sphere* sphere_pt = new Sphere();
	sphere_pt->set_center(0.0);
	sphere_pt->set_radius(85);
	sphere_pt->set_color(1, 0, 0);
	add_object(dynamic_cast <GeometricObject*> (sphere_pt));
}