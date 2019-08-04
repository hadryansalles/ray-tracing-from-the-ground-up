#include "Cylinder.hpp"

Cylinder::Cylinder()
    : Compound() {
    top_disk = new Disk(Point3D(0, 1, 0), Normal(0, 1, 0), 1);
    openc = new OpenCylinder(0, 1, 1);
    bottom_disk = new Disk(Point3D(0, 0, 0), Normal(0, -1, 0), 1);
    add_object(top_disk);
    add_object(openc);
    add_object(bottom_disk);
    set_bbox();
}

Cylinder::Cylinder(float y0_, float y1_, float radius_)
    : Compound() {
    top_disk = new Disk(Point3D(0, y1_, 0), Normal(0, 1, 0), radius_);
    openc = new OpenCylinder(y0_, y1_, radius_);
    bottom_disk = new Disk(Point3D(0, y0_, 0), Normal(0, -1, 0), radius_);
    add_object(top_disk);
    add_object(openc);
    add_object(bottom_disk);
    set_bbox();
}

Cylinder::Cylinder(const Cylinder& cc)
    : Compound() 
    , bbox(cc.bbox) {
    material_ptr = cc.material_ptr;
    top_disk = cc.top_disk->clone();
    openc = cc.openc->clone();
    bottom_disk = cc.bottom_disk->clone();
    add_object(top_disk);
    add_object(openc);
    add_object(bottom_disk);
}

Cylinder* Cylinder::clone() const {
    return (new Cylinder(*this));
}

Cylinder& Cylinder::operator=(const Cylinder& rhs){
    if(this == &rhs){
        return (*this);
    }
    delete_objects();
    Compound::operator=(rhs);
    bbox = rhs.bbox;
    top_disk = rhs.top_disk->clone();
    openc = rhs.openc->clone();
    bottom_disk = rhs.bottom_disk->clone();
    add_object(top_disk);
    add_object(openc);
    add_object(bottom_disk);
    return (*this);
}

void Cylinder::set_radius(const float radius_){
    top_disk->set_radius(radius_);
    openc->set_radius(radius_);
    bottom_disk->set_radius(radius_);
    set_bbox();
}

float Cylinder::get_radius() const{
    return top_disk->get_radius();
}


void Cylinder::set_y0(const float y0_) {
    Point3D center = top_disk->get_center();
    center.y = y0_;
    bottom_disk->set_center(center);
    openc->set_y0(y0_);
    set_bbox();
}

float Cylinder::get_y0() const{
    return openc->get_y0();
}

void Cylinder::set_y1(const float y1_){
    Point3D center = bottom_disk->get_center();
    center.y = y1_;
    top_disk->set_center(center);
    openc->set_y1(y1_);
    set_bbox();
}

float Cylinder::get_y1() const{
    return openc->get_y1();
}

bool Cylinder::hit(const Ray& ray, float& t, ShadeRec& s) const{
    if(bbox.hit(ray)){
        return (Compound::hit(ray, t, s));
    }
    return false;
}

void Cylinder::set_bbox() {
    Point3D center(0, openc->get_y0(), 0); 
    float r = openc->get_radius();
    bbox.p0 = Point3D(center.x - r, center.y,        center.z - r);
    bbox.p1 = Point3D(center.x + r, openc->get_y1(), center.z + r);
}

BBox Cylinder::get_bounding_box() const {
    return bbox;
}