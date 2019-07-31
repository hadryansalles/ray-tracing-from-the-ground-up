#include "Regular.hpp"

Regular::Regular(int samples, int sets) :
    Sampler(samples, sets)
{ }

void Regular::generate_samples(){
    int n = (int) sqrt(num_samples);
	for (int j = 0; j < num_sets; j++)
		for (int p = 0; p < n; p++)		
			for (int q = 0; q < n; q++)
				samples.push_back(Point2D((q + 0.5) / n, (p + 0.5) / n));
}
