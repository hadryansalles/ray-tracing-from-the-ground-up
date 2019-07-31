#include "Sampler.hpp"

Sampler::Sampler(int samples, int sets) :
    num_samples(samples),
    num_sets(sets),
    count(0),
    jump(0) { 
    this->samples.reserve(num_samples*num_sets);
}

Sampler::~Sampler(){
    samples.clear();
}

int Sampler::get_num_samples(){
    return num_samples;
}
void Sampler::set_num_samples(int samples){
    num_samples = samples;
}

int Sampler::get_num_sets(){
    return num_sets;
}
void Sampler::set_num_sets(int sets){
    num_sets = sets;
}

Point2D Sampler::sample_unit_square(){
    if(count % num_samples == 0){
        jump = (rand_int() % num_sets) * num_samples;
    }
    return (samples[jump + (count++)%num_samples]);
}