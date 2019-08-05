#include "Grid.hpp"

Grid::Grid()
    : Compound()
    , bbox()
    , nx(1)
    , ny(1)
    , nz(1)
{}

Grid::Grid(BBox bbox_, int nx_, int ny_, int nz_)
    : Compound()
    , bbox(bbox_)
    , nx(nx_)
    , ny(ny_)
    , nz(nz_)
{}

Grid::Grid(const Grid& grid)
    : Compound(grid)
    , bbox(grid.bbox)
    , nx(grid.nx)
    , ny(grid.ny)
    , nz(grid.nz) {
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