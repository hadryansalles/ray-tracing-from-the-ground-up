#pragma once

void World::build(){
    // view plane
	vp.set_hres(800);
	vp.set_vres(800);
	vp.set_pixel_size(1);
	vp.set_sampler(new NRooks(4));

	background_color = black;

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1);
	set_ambient_light(ambient_ptr);

	tracer_ptr = new RayCast(this);

 	RGBColor yellow(1, 1, 0);
	RGBColor brown(0.71, 0.40, 0.16);
	RGBColor dark_green(0.0, 0.41, 0.41);
	RGBColor orange(1, 0.75, 0);
	RGBColor green(0, 0.6, 0.3);
	RGBColor light_green(0.65, 1, 0.30);
	RGBColor dark_yellow(0.61, 0.61, 0);
    RGBColor blue(0, 0, 1);
	RGBColor light_purple(0.65, 0.3, 1);
	RGBColor dark_purple(0.5, 0, 1);

	ThinLens* pinhole_ptr = new ThinLens(Point3D(0, 0, 4), Point3D(0, 0, -1));
	pinhole_ptr->set_distance(1000);
	pinhole_ptr->set_sampler(new Jittered(100, 100));
	pinhole_ptr->set_lens_radius(0);
	pinhole_ptr->set_focal_dist(60);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* point_light = new PointLight(Vector3D(10, 20, 3), 6);
	add_light(point_light);

    int num_spheres = 1000;
    float volume = 0.1 / num_spheres;
    float radius = pow(0.75*volume/3.1415, 0.33);
    Grid* grid_ptr = new Grid;
    for(int i = 0; i < num_spheres; i++){
        Phong* matte_ptr = new Phong;
        matte_ptr->set_ka(0.25);
        matte_ptr->set_kd(0.75);
		matte_ptr->set_ks(0.5);
        matte_ptr->set_cd(RGBColor(rand_float(), rand_float(), rand_float()));

        Sphere* sphere_ptr = new Sphere;
        sphere_ptr->set_radius(radius);
        sphere_ptr->set_center(Point3D(1.0 - 2.0*rand_float(), 1.0 - 2.0*rand_float(), 1.0 - 2.0*rand_float()));
        sphere_ptr->set_material(matte_ptr);

        grid_ptr->add_object(sphere_ptr);
    }
    grid_ptr->setup_cells();
    add_object(grid_ptr);
}