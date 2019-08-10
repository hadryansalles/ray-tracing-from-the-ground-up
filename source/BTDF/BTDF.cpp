#include "BTDF.hpp"

BTDF::BTDF()
    : sampler_ptr(NULL)
{}

BTDF::BTDF(Sampler* sampler)
    : sampler_ptr(sampler)
{}

BTDF::BTDF(const BTDF& btdf) {
    if(btdf.sampler_ptr){
        sampler_ptr = btdf.sampler_ptr->clone();
    }
}

BTDF& BTDF::operator=(const BTDF& rhs){
    if(this == &rhs){
        return (*this);
    }
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }
    return (*this);
}

BTDF::~BTDF() {
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void BTDF::set_sampler(Sampler* sampler){
    if(sampler_ptr){
        delete sampler_ptr;
    }
    sampler_ptr = sampler;
}

Sampler* BTDF::get_sampler() const {
    return sampler_ptr;
}