#pragma once

#include "../Samplers/Regular.hpp"
#include "../Samplers/Jittered.hpp"
#include "../Samplers/MultiJittered.hpp"

class ViewPlane {
public:
	int hres;   									// horizontal image resolution 
	int vres;   									// vertical image resolution
	float s;										// pixel size

	float gamma;									// gamma correction factor
	float inv_gamma;								// the inverse of the gamma correction factor
	bool show_out_of_gamut;							// display red if RGBColor out of gamut								
	Sampler* sampler_ptr;
	int num_samples;
	int max_depth;

public:
	ViewPlane();   									// default Constructor
	ViewPlane(const ViewPlane& vp);					// copy constructor
	ViewPlane& operator= (const ViewPlane& rhs);	// assignment operator
	~ViewPlane();   								// destructor
					
	void set_hres(const int h_res);
	void set_vres(const int v_res);
	void set_pixel_size(const float size);
	void set_samples(const int samples);
	void set_sampler(Sampler* sampler_p);
	void set_gamma(const float g);
	void set_gamut_display(const bool show);				
	void set_max_depth(const int max_d);
};