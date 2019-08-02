#include "RayCast.hpp"
#include "../World/World.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Materials/Material.hpp"

RayCast::RayCast(World* world_ptr_r):
    Tracer(world_ptr_r)
{}

RGBColor RayCast::trace_ray(const Ray& ray) const{
    ShadeRec sr(world_ptr->hit_objects(ray));
    if(sr.hit_an_object){
        sr.ray = ray;
        return (sr.material_ptr->shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}

RGBColor RayCast::trace_ray(const Ray ray, const int depth) const{
    ShadeRec sr(world_ptr->hit_objects(ray));

    if(sr.hit_an_object){
        sr.ray = ray;
        return (sr.material_ptr->shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}

RGBColor RayCast::trace_ray(const Ray ray, float& tmin, const int depth) const{
    ShadeRec sr(world_ptr->hit_objects(ray));

    if(sr.hit_an_object){
        sr.ray = ray;
        return (sr.material_ptr->shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}