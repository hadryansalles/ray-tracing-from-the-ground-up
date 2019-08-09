#include "Sampler.hpp"

Sampler::Sampler(int samples, int sets) :
    num_samples(samples),
    num_sets(sets),
    count(0),
    jump(0) { 
    //this->samples.reserve(num_samples*num_sets);
}

Sampler::Sampler(const Sampler& samp):
    num_samples(samp.num_samples),
    num_sets(samp.num_sets),
    count(samp.count),
    jump(samp.jump) {
    //this->samples.reserve(num_samples*num_sets);
}

Sampler& Sampler::operator=(const Sampler& rhs){
    if(this == &rhs){
        return (*this);
    }
    this->samples.clear();
    num_samples = rhs.num_samples;
    num_sets = rhs.num_sets;
    count = rhs.count;
    jump = rhs.jump;
    //this->samples.reserve(num_samples*num_sets);  
}

Sampler::~Sampler(){
    samples.clear();
    disk_samples.clear();
    hemisphere_samples.clear();
}

int Sampler::get_num_samples(){
    return num_samples;
}
void Sampler::set_num_samples(int samples){
    num_samples = samples;
    generate_samples();
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

Point3D Sampler::sample_hemisphere(){
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;
		
    return (hemisphere_samples[jump + (count++)%num_samples]);;		
}

void Sampler::map_samples_to_unit_disk(){
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

void Sampler::map_samples_to_hemisphere(const float e){
    int size = samples.size();
    hemisphere_samples.reserve(num_samples*num_sets);
    for(int j = 0; j < size; j++){
        float cos_phi = cos(2.0*PI*samples[j].x);
        float sin_phi = sin(2.0*PI*samples[j].x);
        float cos_theta = pow((1.0*samples[j].y), 1.0/(e+1.0)); 
        float sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        float pu = sin_theta*cos_phi;
        float pv = sin_theta*sin_phi;
        float pw = cos_theta;
        hemisphere_samples.push_back(Point3D(pu, pv, pw));
    }
}

void Sampler::shuffle_y_coordinates() {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i <  num_samples - 1; i++) {
			int target = rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}	
}

void Sampler::shuffle_x_coordinates() {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i <  num_samples - 1; i++) {
			int target = rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}