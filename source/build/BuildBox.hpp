#pragma once

void World::build(){
	// view plane
	vp.set_hres(800);
	vp.set_vres(800);
	vp.set_pixel_size(1);
	vp.set_sampler(new Jittered(4));

	background_color = black;

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->set_ls(1);
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

	ThinLens* pinhole_ptr = new ThinLens(Point3D(10, 60, 60), Point3D(0, -10, -100));
	pinhole_ptr->set_distance(100);
	pinhole_ptr->set_sampler(new Jittered(100, 100));
	pinhole_ptr->set_lens_radius(0);
	pinhole_ptr->set_focal_dist(60);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* point_light = new PointLight(Vector3D(10, 20, 50), 4);
	add_light(point_light);

    //Directional* directional_light = new Directional(Vector3D(0, 0.7, 1), 3.5);
    //add_light(directional_light);

    Box* box;
    Plane* plane;
    Sphere* sphere;
	Triangle* triangle;
	Disk* disk;
	OpenCylinder* openc;
	Cylinder* cylinder;

	float ka = 0.25;
	float kd = 0.75;

	Matte* matte = new Matte;
	matte->set_ka(ka);
	matte->set_kd(kd);
	matte->set_cd(yellow);

	cylinder = new Cylinder(0, 25, 15);
	cylinder->set_material(matte->clone(red));
	add_object(cylinder);

	cylinder = cylinder->clone();
	cylinder->set_y1(45);
	cylinder->set_material(matte->clone(green));
	add_object(cylinder);

    plane = new Plane(Point3D(0), Normal(0, 1, 0));
    plane->set_material(matte->clone(brown));
    add_object(plane);	

	// triangle = new Triangle(Point3D(-20, 0, 0), Point3D(20, 0, 25), Point3D(0, 50, 0));
	// triangle->set_material(matte->clone(red));
	// add_object(triangle);
}