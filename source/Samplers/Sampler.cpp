#include "Sampler.hpp"

Sampler::Sampler(int samples, int sets) :
    num_samples(samples),
    num_sets(sets),
    count(0),
    jump(0) { 
    this->samples.reserve(num_samples*num_sets);
}

Sampler::Sampler(Sampler& samp):
    num_samples(samp.num_samples),
    num_sets(samp.num_sets),
    count(samp.count),
    jump(samp.jump) {
    this->samples.reserve(num_samples*num_sets);
}

Sampler& Sampler::operator=(const Sampler& rhs){
    if(this == &rhs){
        return (*this);
    }
    num_samples = rhs.num_samples;
    num_sets = rhs.num_sets;
    count = rhs.count;
    jump = rhs.jump;
    this->samples.clear();
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

Point2D Sampler::sample_unit_disk(){
    if(count  % num_samples == 0){
        jump = (rand_int() % num_sets) * num_samples;
    }
    return (disk_samples[jump + (count++)%num_samples]);
}

void Sampler::map_samples_to_unit_disk(){
    generate_samples();
    int size = samples.size();
    float r, phi;
    Point2D sp;
    disk_samples.reserve(size);
    for(int j = 0; j < size; j++){
        sp.x = 2.0 * samples[j].x - 1.0;
        sp.y = 2.0 * samples[j].y - 1.0;
        
        if(sp.x > -sp.y){
            if(sp.x > sp.y){
                r = sp.x;
                phi = sp.y / sp.x;
            }
            else{
                r = sp.y;
                phi = 2.0 - sp.x/sp.y;
            }
        }
        else{
            if(sp.x < sp.y){
                r = -sp.x;
                phi = 4.0 + sp.y/sp.x;
            }
            else{
                r = -sp.y;
                if(sp.y != 0.0){
                    phi = 6.0 - sp.x/sp.y;
                }
                else{
                    phi = 0.0;
                }
            }
        }
        phi *= PI/4.0;

        disk_samples[j].x = r * cos(phi);
        disk_samples[j].y = r * sin(phi);
    }
    samples.erase(samples.begin(), samples.end());
}