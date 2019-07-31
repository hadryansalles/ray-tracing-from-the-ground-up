void World::build(void) {
    vp.set_hres(800);
	vp.set_vres(800);
	vp.set_pixel_size(.020);
	vp.set_gamma(1.0);
	vp.set_sampler(new Regular(16));
	
	background_color = black;
	tracer_ptr = new Sinusoid(this);
}