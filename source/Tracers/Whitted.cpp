#include "Whitted.hpp"
#include "../World/World.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Materials/Material.hpp"

Whitted::Whitted(World* world_ptr_r):
    Tracer(world_ptr_r)
{}

RGBColor Whitted::trace_ray(const Ray& ray) const{
    printf("error. Whitted::trace_ray without depth.\n");
    return black;
}

RGBColor Whitted::trace_ray(const Ray ray, const int depth) const{
    if(depth > world_ptr->vp.max_depth){
        return black;
    }
    else {
        ShadeRec sr(world_ptr->hit_objects(ray));
        if(sr.hit_an_object){
            sr.ray = ray;
            sr.depth = depth;
            return (sr.material_ptr->shade(sr));
        }
        else{
            return (world_ptr->background_color);
        }
    }
}

RGBColor Whitted::trace_ray(const Ray ray, float& tmin, const int depth) const{
    if(depth > world_ptr->vp.max_depth){
        return black;
    }
    else {
        ShadeRec sr(world_ptr->hit_objects(ray));
        if(sr.hit_an_object){
            sr.depth = depth;
            sr.ray = ray;
            return (sr.material_ptr->shade(sr));
        }
        else{
            return (world_ptr->background_color);
        }
    }
}