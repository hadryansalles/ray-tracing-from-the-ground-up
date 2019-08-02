#pragma once

void World::build(void){
    vp.hres = 400;
    vp.vres = 400;
    vp.set_pixel_size(1);
    vp.set_gamma(1);
    vp.set_num_samples(1);
    background_color = black;
    tracer_ptr = new RayCast(this);

    Pinhole* pin = new Pinhole(Point3D(0, 0, 100), Point3D(0, 0, -100));
    pin->set_distance(100);
    set_camera(pin);

    ambient_ptr = new Ambient;

    Sphere* sphere = new Sphere(Point3D(0, 0, 0), 50);
    Matte* matte = new Matte;
    sphere->set_material(matte);
    add_object(sphere);
}