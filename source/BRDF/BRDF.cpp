#include "BRDF.hpp"

BRDF::BRDF():
    sampler_ptr(NULL)
{}

BRDF::BRDF(Sampler* sampler):
    sampler_ptr(sampler)
{}

BRDF::~BRDF(){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void BRDF::set_sampler(Sampler* sampler){
    sampler_ptr = sampler;
}

Sampler* BRDF::get_sampler() const {
    return sampler_ptr;
}