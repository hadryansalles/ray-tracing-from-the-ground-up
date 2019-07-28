void 												
World::build(void) {
   vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	
	background_color = white;
	tracer_ptr = new SingleSphere(this); 
	
	sphere.set_center(0.0);
	sphere.set_radius(85);
}
