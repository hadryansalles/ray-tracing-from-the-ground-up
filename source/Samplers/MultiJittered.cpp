#include "MultiJittered.hpp"

MultiJittered::MultiJittered(const int num_samples, const int m)
	: Sampler(num_samples, m) {
	generate_samples();
}

MultiJittered::MultiJittered(const MultiJittered& rhs)			
	: Sampler(rhs) {
	generate_samples();
}

MultiJittered& MultiJittered::operator= (const MultiJittered& rhs) {
	if (this == &rhs) {		
		return (*this);
	}
	Sampler::operator=(rhs);
	return (*this);
}

MultiJittered* MultiJittered::clone() const {
	return (new MultiJittered(*this));
}

MultiJittered::~MultiJittered() 
{}

void MultiJittered::generate_samples() {		
	int n = (int)sqrt((float)num_samples);
	float subcell_width = 1.0 / ((float) num_samples);
	
	Point2D fill_point;
	for (int j = 0; j < num_samples * num_sets; j++)
		samples.push_back(fill_point);
			
	for (int p = 0; p < num_sets; p++) 
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				samples[i * n + j + p * num_samples].x = (i * n + j) * subcell_width + rand_float()*subcell_width;
				samples[i * n + j + p * num_samples].y = (j * n + i) * subcell_width + rand_float()*subcell_width;
			}

	for (int p = 0; p < num_sets; p++) 
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				int k = j + rand_int()%n;
				float t = samples[i * n + j + p * num_samples].x;
				samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
				samples[i * n + k + p * num_samples].x = t;
			}

	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				int k = j + rand_int()%n;
				float t = samples[j * n + i + p * num_samples].y;
				samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
				samples[k * n + i + p * num_samples].y = t;
		}
}