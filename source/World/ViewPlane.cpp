#include "ViewPlane.hpp"
							
ViewPlane::ViewPlane(void)							
	: 	hres(400), 
		vres(400),
		s(1.0),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false),
		num_samples(1),
		sampler_ptr(new Regular())
{}

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		num_samples(vp.num_samples),
		sampler_ptr(vp.sampler_ptr)
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
	sampler_ptr 		= rhs.sampler_ptr;

	return (*this);
}

ViewPlane::~ViewPlane(void) {
	if(sampler_ptr){
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

void ViewPlane::set_num_samples(const int num_samples){
	if(num_samples != 1){
		delete sampler_ptr;
		sampler_ptr = new Jittered(num_samples);
		this->num_samples = num_samples;
	}
}

void ViewPlane::set_sampler(Sampler* sampler_p){
	if(sampler_p != NULL && sampler_p->get_num_samples() != 1){
		sampler_ptr = sampler_p;
		num_samples = sampler_p->get_num_samples();
	}
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