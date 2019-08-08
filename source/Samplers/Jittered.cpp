#include "Jittered.hpp"
#include <stdio.h>

Jittered::Jittered(int samples, int sets) :
    Sampler(samples, sets) {
    generate_samples();
}

Sampler* Jittered::clone() const{
    return (new Jittered(*this));
}

void Jittered::generate_samples(){
    printf("Gerou jittered.\n");
    int n = (int) sqrt(num_samples);
    for(int p = 0; p < num_sets; p++){
        
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                Point2D sp( (k + rand_float())/n,
                            (j + rand_float())/n );
                samples.push_back(sp);
            }
        }
    }
}
