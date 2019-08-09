#pragma once

void World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600); 
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	tracer_ptr = new Whitted(this);	
	background_color = RGBColor(0.1); 
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(75, 40, 100); 
	pinhole_ptr->set_lookat(-10, 39, 0);  
	pinhole_ptr->set_view_distance(360);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(150, 150, 0);  
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	// yellow-green reflective sphere
	
	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_ka(0.25); 
	reflective_ptr1->set_kd(0.5);
	reflective_ptr1->set_cd(0.75, 0.75, 0);    	// yellow
	reflective_ptr1->set_ks(0.15);
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_cr(white); 			// default color
	
	float radius = 23.0;
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, radius, -25), radius); 
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	
	
	// orange non-reflective sphere
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.45); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.75, 0.25, 0);   // orange
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-7, 10, 42), 20);
	sphere_ptr2->set_material(matte_ptr1);      
	add_object(sphere_ptr2);
	
	
	// sphere on top of box

	Reflective* reflective_ptr2 = new Reflective;			
	reflective_ptr2->set_ka(0.35); 
	reflective_ptr2->set_kd(0.75);
	reflective_ptr2->set_cd(black); 
	reflective_ptr2->set_ks(0.0);		// default value
	reflective_ptr2->set_exp(1.0);		// default value, but irrelevant in this case
	reflective_ptr2->set_kr(0.75);
	reflective_ptr2->set_cr(white); 

	Sphere* sphere_ptr3 = new Sphere(Point3D(-30, 59, 35), 20);
	sphere_ptr3->set_material(reflective_ptr2);     
	add_object(sphere_ptr3);

	
	// cylinder
	
	Reflective* reflective_ptr3 = new Reflective;			
	reflective_ptr3->set_ka(0.35); 
	reflective_ptr3->set_kd(0.5);
	reflective_ptr3->set_cd(0, 0.5, 0.75);   // cyan
	reflective_ptr3->set_ks(0.2);
	reflective_ptr3->set_exp(100.0);
	reflective_ptr3->set_kr(0.75);
	reflective_ptr3->set_cr(white);
	
	double bottom 			= 0.0;
	double top 				= 85;   
	double cylinder_radius	= 22;
	Cylinder* cylinder_ptr = new Cylinder(bottom, top, cylinder_radius);
	cylinder_ptr->set_material(reflective_ptr3);
	add_object(cylinder_ptr);
	
	
	// box
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.15); 
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.75, 1.0, 0.75);   // light green
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(matte_ptr2);
	add_object(box_ptr);


	Plane* plane = new Plane(Point3D(0), Normal(0, 1, 0));
	plane->set_material(matte_ptr2->clone(white));
	add_object(plane);
}