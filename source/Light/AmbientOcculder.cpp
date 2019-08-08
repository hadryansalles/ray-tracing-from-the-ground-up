#include "AmbientOccluder.hpp"
#include "../Samplers/MultiJittered.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../World/World.hpp"

AmbientOccluder::AmbientOccluder()
    : u(0)
    , v(0)
    , w(0)
    , sampler_ptr(new Regular(1)) {
    sampler_ptr->map_samples_to_hemisphere(1);
}
AmbientOccluder::AmbientOccluder(const AmbientOccluder& amb)
    : u(amb.u)
    , v(amb.v)
    , w(amb.w) {
    if(amb.sampler_ptr){
        sampler_ptr = amb.sampler_ptr->clone();
    }
    else{
        sampler_ptr = new Regular(1);
    }
    sampler_ptr->map_samples_to_hemisphere(1);
}

AmbientOccluder& AmbientOccluder::operator=(const AmbientOccluder& rhs){
    if(this == &rhs){
        return (*this);
    }    
    Light::operator=(rhs);
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;
    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }
    else{
        sampler_ptr = new MultiJittered(4);
    }
    sampler_ptr->map_samples_to_hemisphere(1);
    return (*this);
}

AmbientOccluder* AmbientOccluder::clone() const {
    return (new AmbientOccluder(*this));
}

void AmbientOccluder::set_sampler(Sampler* s_ptr){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    sampler_ptr = s_ptr;
    sampler_ptr->map_samples_to_hemisphere(1);
}

void AmbientOccluder::set_min_amount(float r, float g, float b){
    min_amount = RGBColor(r, g, b);
}

void AmbientOccluder::set_min_amount(float a){
    min_amount = RGBColor(a);
}

void AmbientOccluder::set_min_amount(RGBColor min){
    min_amount = min;
}

Vector3D AmbientOccluder::get_direction(ShadeRec& sr){
    Point3D sp = sampler_ptr->sample_hemisphere();
    return (sp.x*u + sp.y*v + sp.z*w);
}

bool AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const{
    float t;
    int num_objects = sr.w.objects.size();
    for(int j = 0; j < num_objects; j++){
        if(sr.w.objects[j]->shadow_hit(ray, t)){
            return true;
        }
    }
    return false;
}

RGBColor AmbientOccluder::L(ShadeRec& sr){
    w = sr.normal;
    v = w ^ Vector3D(0.00072, 1.0, 0.0034);
    v.normalize();
    u = v ^ w;
    Ray shadow_ray;
    shadow_ray.o = sr.hit_point;
    shadow_ray.d = get_direction(sr);
    if(in_shadow(shadow_ray, sr)){
        return (min_amount*ls*color);
    }
    else{
        return (ls*color);
    }
}