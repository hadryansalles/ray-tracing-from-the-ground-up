#pragma once

#include "GeometricObject.hpp"
#include "../Samplers/Regular.hpp"

class Rectangle : public GeometricObject {
private:
    Point3D p0;
    Vector3D a;
    Vector3D b;
    Normal normal;
    Sampler* sampler_ptr;
    float area;
    float inv_area;
    float a_len_squared;
    float b_len_squared;

public:
    Rectangle(Point3D p0_ = Point3D(0), Vector3D a_ = Vector3D(0), Vector3D b_ = Vector3D(0), Normal n = Normal(0));
    Rectangle(const Rectangle& rect);
    Rectangle& operator=(const Rectangle& rhs);
    Rectangle* clone() const;

    ~Rectangle();

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const; 	
	virtual bool shadow_hit(const Ray& ray, float& tmin) const;											 

    void set_p0(const Point3D p0_);
    Point3D get_p0() const;
    void set_a_b(const Vector3D a_, const Vector3D b_);

    void set_sampler(Sampler* sampler);
    virtual Point3D sample();
    virtual float pdf(const ShadeRec& sr);
  
    virtual Normal get_normal() const;
    virtual Normal get_normal(const Point3D& p) const;
};