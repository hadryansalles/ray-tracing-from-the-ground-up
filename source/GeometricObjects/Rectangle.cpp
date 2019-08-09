#include "Rectangle.hpp"

Rectangle::Rectangle(Point3D p0_, Vector3D a_, Vector3D b_, Normal n)
    : GeometricObject()
    , p0(p0_)
    , a(a_)
    , b(b_)
    , normal(n) 
    , sampler_ptr(new Regular(1)) 
    , area(a.length() * b.length())
    , inv_area(1.0/area)
    , a_len_squared(a.length()*a.length())
    , b_len_squared(b.length()*b.length()) {
    normal.normalize();
}

Rectangle::Rectangle(const Rectangle& rect)
    : GeometricObject(rect)
    , p0(rect.p0)
    , a(rect.a)
    , b(rect.b)
    , normal(rect.normal) 
    , area(rect.area)
    , inv_area(rect.inv_area)
    , a_len_squared(rect.a_len_squared)
    , b_len_squared(rect.b_len_squared) {
    if(rect.sampler_ptr){
        sampler_ptr = rect.sampler_ptr->clone();
    }       
    else{
        sampler_ptr = new Regular(1);
    }
}

Rectangle& Rectangle::operator=(const Rectangle& rhs){
    if(this == &rhs){
        return (*this);
    }
    GeometricObject::operator=(rhs);
    p0 = rhs.p0;
    a = rhs.a;
    b = rhs.b;
    normal = rhs.b;
    area = rhs.area;
    inv_area = rhs.inv_area;
    a_len_squared = rhs.a_len_squared;
    b_len_squared = rhs.b_len_squared;
    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }       
    else{
        sampler_ptr = new Regular(1);
    }
    return (*this);
}

Rectangle* Rectangle::clone() const {
    return (new Rectangle(*this));
}

Rectangle::~Rectangle(){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void Rectangle::set_p0(const Point3D p0_){
    p0 = p0_;
}

Point3D Rectangle::get_p0() const {
    return p0;
}

void Rectangle::set_a_b(const Vector3D a_, const Vector3D b_){
    a = a_;
    b = b_;
    normal = a ^ b;
    normal.normalize();
    area = a.length() * b.length();
    inv_area = 1.0/area;
    a_len_squared = a.length()*a.length();
    b_len_squared = b.length()*b.length();
}

void Rectangle::set_sampler(Sampler* sampler){
    if(sampler_ptr){
        delete sampler_ptr;
    }
    sampler_ptr = sampler;
}

Point3D Rectangle::sample(){
    Point2D sample_point = sampler_ptr->sample_unit_square();
    return (p0 + sample_point.x*a + sample_point.y*b);
}

float Rectangle::pdf(const ShadeRec& sr){
    return inv_area;
}

Normal Rectangle::get_normal(const Point3D& p) const{
    return normal;
}

Normal Rectangle::get_normal() const{
    return normal;
}

bool Rectangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const{
    double t = (p0 - ray.o) * normal / (ray.d * normal); 
	
	if (t <= kEpsilon)
		return (false);
			
	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
	tmin 				= t;
	sr.normal 			= normal;
	sr.local_hit_point 	= p;
	
	return (true);
}

bool Rectangle::shadow_hit(const Ray& ray, float& tmin) const{
    double t = (p0 - ray.o) * normal / (ray.d * normal); 
	
	if (t <= kEpsilon)
		return (false);
			
	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
	tmin 				= t;
	return (true);
}											 
