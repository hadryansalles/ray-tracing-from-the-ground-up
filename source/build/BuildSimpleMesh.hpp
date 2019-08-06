#pragma once

void World::build() {
	int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_num_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);
	
	background_color = black;

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(Point3D(100, 50, 90));
	pinhole_ptr->set_lookat(Point3D(0, -0.5, 0));
	pinhole_ptr->set_distance(16000);  	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
		
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(Point3D(0.75, 1, -0.15));     
	directional_ptr->set_ls(4.5);  
	add_light(directional_ptr);
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.1); 
	matte_ptr1->set_kd(0.75);   
	matte_ptr1->set_cd(RGBColor(0.1, 0.5, 1.0));
	 	
	char* file_name;
	strcpy(file_name, "TwoTriangles.ply");
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_flat_triangles(file_name);		// for Figure 23.7(a)
//	grid_ptr->read_smooth_triangles(file_name);		// for Figure 23.7(b)
	grid_ptr->set_material(matte_ptr1);   
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(RGBColor(1, 0.9, 0.6));
	matte_ptr2->set_ka(0.25); 
	matte_ptr2->set_kd(0.4);
		
	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));  
	plane_ptr1->set_material(matte_ptr2);
	add_object(plane_ptr1);	
}