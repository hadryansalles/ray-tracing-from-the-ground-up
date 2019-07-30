#pragma once

class ViewPlane {
public:
	int hres;   									// horizontal image resolution 
	int vres;   									// vertical image resolution
	float s;										// pixel size

	float gamma;									// gamma correction factor
	float inv_gamma;								// the inverse of the gamma correction factor
	bool show_out_of_gamut;							// display red if RGBColor out of gamut								

	int num_samples;

public:
	ViewPlane();   									// default Constructor
	ViewPlane(const ViewPlane& vp);					// copy constructor
	ViewPlane& operator= (const ViewPlane& rhs);	// assignment operator
	~ViewPlane();   								// destructor
					
	void set_hres(const int h_res);
	void set_vres(const int v_res);
	void set_pixel_size(const float size);
	void set_num_samples(const int num_samples);
	void set_gamma(const float g);
	void set_gamut_display(const bool show);				
};