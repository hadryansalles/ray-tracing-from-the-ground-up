void World::build(){
    vp.set_vres(800);
    vp.set_hres(800);
    vp.set_pixel_size(1);
    background_color = RGBColor(1);
    tracer_ptr = new MultipleObjects(this);

    ThinLens* thin = new ThinLens(Point3D(0, 100, 0), Point3D(0, 0, -100));
    thin->set_sampler(new Jittered(100));
    thin->set_distance(120);
    thin->set_focal_dist(130);
    thin->set_lens_radius(1);
    thin->compute_uvw();
    camera = thin;

    //Plane* plane_pt = new Plane(Point3D(0), Normal(0, 1, 0));
    //plane_pt->set_color(RGBColor(0));
    //add_object(plane_pt);

    Sphere* sphere_pt;
    for(int i = 0; i < 3; i++){
        sphere_pt = new Sphere(Point3D(-150 + i*i*200, 0, -80-140*i), 60);
        sphere_pt->set_color(RGBColor(rand_float(), rand_float(), rand_float()));
        add_object(sphere_pt);
    }
}