#include "Grid.hpp"
#include "MeshTriangle.hpp"
#include "FlatMeshTriangle.hpp"
#include "SmoothMeshTriangle.hpp"
#include "Triangle.hpp"
#include "../Utilities/ply.hpp"

typedef enum {
	flat, 
	smooth
} TriangleType;


Grid::Grid()
    : Compound()
    , bbox()
    , nx(1)
    , ny(1)
    , nz(1)
	, mesh_ptr(new Mesh)
	, reverse_normal(false)
{}

Grid::Grid(Mesh* mesh_ptr_)
    : Compound()
    , bbox()
    , nx(0)
    , ny(0)
    , nz(0)
	, mesh_ptr(mesh_ptr_)
	, reverse_normal(false)
{}

Grid::Grid(BBox bbox_, int nx_, int ny_, int nz_)
    : Compound()
    , bbox(bbox_)
    , nx(nx_)
    , ny(ny_)
    , nz(nz_)
	, mesh_ptr(new Mesh)
	, reverse_normal(false)
{}

Grid::Grid(const Grid& grid)
    : Compound(grid)
    , bbox(grid.bbox)
    , nx(grid.nx)
    , ny(grid.ny)
    , nz(grid.nz)
	, reverse_normal(false) {
    if(grid.mesh_ptr){
		mesh_ptr = grid.mesh_ptr->clone();
	}
	
	cells.reserve(grid.cells.size());
    for(int i = 0; i < grid.cells.size(); i++){
        cells[i] = grid.cells[i]->clone();
    }
}

Grid& Grid::operator=(const Grid& rhs){
    if(this == &rhs){
        return (*this);
    }
    Compound::operator=(rhs);
    cells.reserve(rhs.cells.size());
    for(int i = 0; i < rhs.cells.size(); i++){
        cells[i] = rhs.cells[i]->clone();
    }
    bbox = rhs.bbox;
    nx = rhs.nx;
    ny = rhs.ny;
    nz = rhs.nz;
    return (*this);
}

Grid* Grid::clone() const{
    return (new Grid(*this));
}

BBox Grid::get_bounding_box() const{
    return bbox;
}

void Grid::set_bouding_box(const BBox bbox_){
    bbox = bbox_;
}

void Grid::set_number_cells(const int nx_, const int ny_, const int nz_){
    nx = nx_;
    ny = ny_;
    nz = nz_;
}

void Grid::setup_cells(){
    Point3D p0 = min_coordinates();
    Point3D p1 = max_coordinates();
    bbox.p0 = p0;
    bbox.p1 = p1;

    int num_objects = objects.size();
    float wx = p1.x - p0.x;
    float wy = p1.y - p0.y;
    float wz = p1.z - p0.z;
    float multiplier = 2.0;
    float s = pow(wx*wy*wz/num_objects, 0.33333);
    nx = multiplier*wx/s + 1;
    ny = multiplier*wy/s + 1;
    nz = multiplier*wz/s + 1;

    float num_cells = nx*ny*nz;
    cells.clear();
    cells.reserve(num_cells);
    for(int i = 0; i < num_cells; i++){
        cells.push_back(NULL);
    }

    std::vector<int> counts;
    counts.reserve(num_cells);
    for(int i = 0; i < num_cells; i++){
        counts.push_back(0);
    }
    BBox obj_bbox;
    int index;
    for(int i = 0; i < num_objects; i++){

        obj_bbox = objects[i]->get_bounding_box();

        int ixmin = clamp((obj_bbox.p0.x - p0.x)*nx/(wx), 0, nx - 1);
        int iymin = clamp((obj_bbox.p0.y - p0.y)*ny/(wy), 0, ny - 1);
        int izmin = clamp((obj_bbox.p0.z - p0.z)*nz/(wz), 0, nz - 1);

        int ixmax = clamp((obj_bbox.p1.x - p0.x)*nx/(wx), 0, nx - 1);
        int iymax = clamp((obj_bbox.p1.y - p0.y)*ny/(wy), 0, ny - 1);
        int izmax = clamp((obj_bbox.p1.z - p0.z)*nz/(wz), 0, nz - 1);

        for(int iz = izmin; iz <= izmax; iz++){
            for(int iy = iymin; iy <= iymax; iy++){
                for(int ix = ixmin; ix <= ixmax; ix++){
                    index = ix + nx*iy + nx*ny*iz;
                    if(counts[index] == 0){
                        cells[index] = objects[i];
                        counts[index] += 1;
                    }
                    else{
                        if(counts[index] == 1){
                            Compound* compound_ptr = new Compound();
                            compound_ptr->add_object(cells[index]);
                            compound_ptr->add_object(objects[i]);

                            cells[index] = compound_ptr;
                            counts[index] += 1;
                        }
                        else{
                            cells[index]->add_object(objects[i]);
                            counts[index] += 1;
                        }
                    }
                }
            }
        }
    }
    
    counts.clear();  
}

bool Grid::hit(const Ray& ray, float& t, ShadeRec& s) const {
    double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

    double x0 = bbox.p0.x;
    double y0 = bbox.p0.y;
    double z0 = bbox.p0.z;
    double x1 = bbox.p1.x;
    double y1 = bbox.p1.y;
    double z1 = bbox.p1.z;
	
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max; 
	
	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}
	
	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}
	
	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}
	
	double t0, t1;
	
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;
		
	if (tz_min > t0)
		t0 = tz_min;
		
	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
		
	if (tz_max < t1)
		t1 = tz_max;
			
	if (t0 > t1)
		return(false);
	
	int ix, iy, iz;
	
	if (bbox.inside(ray.o)) {  			
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else {
		Point3D p = ray.o + t0 * ray.d;  
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	
	double dtx = (tx_max - tx_min) / nx;
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;
		
	double 	tx_next, ty_next, tz_next;
	int 	ix_step, iy_step, iz_step;
	int 	ix_stop, iy_stop, iz_stop;
	
	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}
	
	if (dx == 0.0) {
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}
	
	
	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}
	
	if (dy == 0.0) {
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}
		
	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}
	
	if (dz == 0.0) {
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}
	
	while (true) {	
		GeometricObject* object_ptr = cells[ix + nx * iy + nx * ny * iz];
		
		if (tx_next < ty_next && tx_next < tz_next) {
			if (object_ptr && object_ptr->hit(ray, t, s) && t < tx_next) {
				material_ptr = object_ptr->get_material();
				return (true);
			}
			
			tx_next += dtx;
			ix += ix_step;
						
			if (ix == ix_stop)
				return (false);
		} 
		else { 	
			if (ty_next < tz_next) {
				if (object_ptr && object_ptr->hit(ray, t, s) && t < ty_next) {
					material_ptr = object_ptr->get_material();
                    return (true);
				}
				
				ty_next += dty;
				iy += iy_step;
								
				if (iy == iy_stop)
					return (false);
		 	}
		 	else {		
				if (object_ptr && object_ptr->hit(ray, t, s) && t < tz_next) {
					material_ptr = object_ptr->get_material();
                    return (true);
				}
				
				tz_next += dtz;
				iz += iz_step;
								
				if (iz == iz_stop)
					return (false);
		 	}
		}
	}
}

Point3D Grid::min_coordinates(){
    BBox bbox_;
    Point3D p0(kHugeValue);
    int num_objects = objects.size();
    for(int i = 0; i < num_objects; i++){
        bbox_ = objects[i]->get_bounding_box();
        if(bbox_.p0.x < p0.x){
            p0.x = bbox_.p0.x;
        }
        if(bbox_.p0.y < p0.y){
            p0.y = bbox_.p0.y;
        }
        if(bbox_.p0.z < p0.z){
            p0.z = bbox_.p0.z;
        }
    }
    p0.x -= kEpsilon;
    p0.y -= kEpsilon;
    p0.z -= kEpsilon;
    return p0;
}

Point3D Grid::max_coordinates(){
    BBox bbox_;
    Point3D p1(-kHugeValue);
    int num_objects = objects.size();
    for(int i = 0; i < num_objects; i++){
        bbox_ = objects[i]->get_bounding_box();
        if( bbox_.p1.x > p1.x){
            p1.x = bbox_.p1.x;
        }
        if( bbox_.p1.y > p1.y){
            p1.y = bbox_.p1.y;
        }
        if( bbox_.p1.z > p1.z){
            p1.z = bbox_.p1.z;
        }
    }
    p1.x += kEpsilon;
    p1.y += kEpsilon;
    p1.z += kEpsilon;
    return p1;
}

void Grid::compute_mesh_normals() {
	mesh_ptr->normals.reserve(mesh_ptr->num_vertices);
	
	for (int index = 0; index < mesh_ptr->num_vertices; index++) {   // for each vertex
		Normal normal;    // is zero at this point	
			
		for (int j = 0; j < mesh_ptr->vertex_faces[index].size(); j++)
			normal += objects[mesh_ptr->vertex_faces[index][j]]->get_normal();  
	
		// The following code attempts to avoid (nan, nan, nan) normalised normals when all components = 0
		
		if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0)
			normal.y = 1.0;
		else 
			normal.normalize();     
		
		mesh_ptr->normals.push_back(normal);
	}
	
	// erase the vertex_faces arrays because we have now finished with them
	
	for (int index = 0; index < mesh_ptr->num_vertices; index++)
		for (int j = 0; j < mesh_ptr->vertex_faces[index].size(); j++)
			mesh_ptr->vertex_faces[index].erase (mesh_ptr->vertex_faces[index].begin(), mesh_ptr->vertex_faces[index].end());
	
	mesh_ptr->vertex_faces.erase (mesh_ptr->vertex_faces.begin(), mesh_ptr->vertex_faces.end());

	std::cout << "finished constructing normals" << std::endl;
}

void Grid::read_ply_file(char* file_name, const int triangle_type) {
	// Vertex definition 
	
	typedef struct Vertex {
	  float x,y,z;      // space coordinates       
	} Vertex;
	
	// Face definition. This is the same for all files but is placed here to keep all the definitions together

	typedef struct Face {
	  	unsigned char nverts;    // number of vertex indices in list
	  	int* verts;              // vertex index list 
	} Face;
		
	// list of property information for a vertex
	// this varies depending on what you are reading from the file

	PlyProperty vert_props[] = {
	  {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
	  {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
	  {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0}
	};

	// list of property information for a face. 
	// there is a single property, which is a list
	// this is the same for all files

	PlyProperty face_props[] = { 
	  	{"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
	   		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)}
	};
	
	// local variables
	
	int 			i,j;
  	PlyFile*		ply;
  	int 			nelems;		// number of element types: 2 in our case - vertices and faces
  	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	Vertex**		vlist;
	Face**			flist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


  	// open a ply file for reading
  
	ply = ply_open_for_reading(file_name, &nelems, &elist, &file_type, &version);
	
  	// print what we found out about the file
	std::cout << file_name << std::endl;
  	printf ("version %f\n", version);
  	printf ("type %d\n", file_type);
  	
  	// go through each kind of element that we learned is in the file and read them 
	printf("ates do for %d.\n", nelems);
  	for (i = 0; i < nelems; i++) {  // there are only two elements in our files: vertices and faces
	    // get the description of the first element 
  	    elem_name = elist[i];
	    plist = ply_get_element_description (ply, elem_name, &num_elems, &nprops);

	    // print the name of the element, for debugging
	    
		std::cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << std::endl;

	    // if we're on vertex elements, read in the properties
    
    	if (equal_strings ("vertex", elem_name)) {
	      	// set up for getting vertex elements
	      	// the three properties are the vertex coordinates
	
			ply_get_property (ply, elem_name, &vert_props[0]);
	      	ply_get_property (ply, elem_name, &vert_props[1]);
		  	ply_get_property (ply, elem_name, &vert_props[2]);
		  	
		  	// reserve mesh elements
		  	
		  	mesh_ptr->num_vertices = num_elems;
		  	mesh_ptr->vertices.reserve(num_elems);

		  	// grab all the vertex elements
		  			  
		  	for (j = 0; j < num_elems; j++) {
				Vertex* vertex_ptr = new Vertex;

		        // grab an element from the file
		        
				ply_get_element (ply, (void *) vertex_ptr);
		  		mesh_ptr->vertices.push_back(Point3D(vertex_ptr->x, vertex_ptr->y, vertex_ptr->z));
		  		delete vertex_ptr;
		  	}
    	}

	    // if we're on face elements, read them in 
	    
	    if (equal_strings ("face", elem_name)) {
		    // set up for getting face elements
		
			ply_get_property (ply, elem_name, &face_props[0]);   // only one property - a list
			
		  	mesh_ptr->num_triangles = num_elems;
		  	objects.reserve(num_elems);  // triangles will be stored in Compound::objects
		
			// the following code stores the face numbers that are shared by each vertex
		  	
		  	mesh_ptr->vertex_faces.reserve(mesh_ptr->num_vertices);
		  	std::vector<int> faceList;
		  			  	
		  	for (j = 0; j < mesh_ptr->num_vertices; j++) 
		  		mesh_ptr->vertex_faces.push_back(faceList); // store empty lists so that we can use the [] notation below
		  			
			// grab all the face elements
			
			int count = 0; // the number of faces read
					      
			for (j = 0; j < num_elems; j++) {
			    // grab an element from the file 
			    
			    Face* face_ptr = new Face;
			    
			    ply_get_element (ply, (void *) face_ptr);
			    
			    // construct a mesh triangle of the specified type
			    
			    if (triangle_type == flat) {
			    	FlatMeshTriangle* triangle_ptr = new FlatMeshTriangle(mesh_ptr, face_ptr->verts[0], face_ptr->verts[1], face_ptr->verts[2]);
					triangle_ptr->compute_normal(reverse_normal);		
					objects.push_back(triangle_ptr); 
				} 
			    	
			    if (triangle_type == smooth) {
			    	SmoothMeshTriangle* triangle_ptr = new SmoothMeshTriangle(mesh_ptr, face_ptr->verts[0], face_ptr->verts[1], face_ptr->verts[2]);
					triangle_ptr->compute_normal(reverse_normal); 	// the "flat triangle" normal is used to compute the average normal at each mesh vertex
					objects.push_back(triangle_ptr); 				// it's quicker to do it once here, than have to do it on average 6 times in compute_mesh_normals
					
					// the following code stores a list of all faces that share a vertex
					// it's used for computing the average normal at each vertex in order(num_vertices) time
					
					mesh_ptr->vertex_faces[face_ptr->verts[0]].push_back(count);
					mesh_ptr->vertex_faces[face_ptr->verts[1]].push_back(count);
					mesh_ptr->vertex_faces[face_ptr->verts[2]].push_back(count);
					count++;
				} 
			}
			
			if (triangle_type == flat)
				mesh_ptr->vertex_faces.erase(mesh_ptr->vertex_faces.begin(), mesh_ptr->vertex_faces.end());
	    }
    
	    // print out the properties we got, for debugging
	    
	    for (j = 0; j < nprops; j++)
	    	printf ("property %s\n", plist[j]->name);
	
	}  // end of for (i = 0; i < nelems; i++) 


	// grab and print out the comments in the file
	  
	comments = ply_get_comments (ply, &num_comments);
	  
	for (i = 0; i < num_comments; i++)
	    printf ("comment = '%s'\n", comments[i]);

	// grab and print out the object information
	  
	obj_info = ply_get_obj_info (ply, &num_obj_info);
	  
	for (i = 0; i < num_obj_info; i++)
	    printf ("obj_info = '%s'\n", obj_info[i]);

	// close the ply file 
	  
	ply_close (ply);
}

void Grid::read_flat_triangles(char* file_name) {
  	read_ply_file(file_name, flat);
}

void Grid::read_smooth_triangles(char* file_name) {
  	read_ply_file(file_name, smooth);
  	compute_mesh_normals();
}