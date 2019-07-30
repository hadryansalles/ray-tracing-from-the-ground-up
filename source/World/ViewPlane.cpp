#include "ViewPlane.hpp"
							
ViewPlane::ViewPlane(void)							
	: 	hres(400), 
		vres(400),
		s(1.0),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false),
		num_samples(1)
{}

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		num_samples(vp.num_samples)
{}

ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;
	num_samples 		= rhs.num_samples;
	
	return (*this);
}

ViewPlane::~ViewPlane(void) {}

void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

void ViewPlane::set_num_samples(const int num_samples){
	this->num_samples = num_samples;
}

void ViewPlane::set_pixel_size(const float size) {
	s = size;
}

void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}

void ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}