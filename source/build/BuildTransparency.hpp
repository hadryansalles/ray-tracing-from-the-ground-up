#pragma once

void World::build(){
    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_samples(4);
    vp.set_max_depth(10);
    tracer_ptr = new Whitted(this);
    Pinhole* pin = new Pinhole(Point3D(0, 4, 10), Point3D(0, 0, -5));
    pin->set_view_distance(120);
    pin->compute_uvw();
    set_camera(pin);
    background_color = RGBColor(0.7, 0.7, 0.7);

    PointLight* plight = new PointLight();
    plight->set_location(0, 10, 10);
    plight->set_shadows(true);
    plight->scale_radiance(2);
    plight->set_color(RGBColor(1));
    add_light(plight);

    Matte* matte = new Matte();
    matte->set_cd(0.9);
    matte->set_ka(0.25);
    matte->set_kd(0.75);

    Plane* plane = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane->set_material(matte);
    add_object(plane);

    Transparent* transp = new Transparent();
    transp->set_ks(0.5);
    transp->set_exp(2000.0);
    transp->set_ior(1.5);
    transp->set_kr(0.1);
    transp->set_kt(0.9);

    Cylinder* rect = new Cylinder(0, 5, 3);
    cyl->set_material(transp);
    add_object(cyl);

    Sphere* sphere = new Sphere(Point3D(0, 4, -6), 3);
    sphere->set_material(matte->clone(RGBColor(1, 0, 0)));
    add_object(sphere);
}