#pragma once

#include "Sampler.hpp"

class NRooks: public Sampler {
public:
	NRooks(const int num_samples = 1, const int m = 50);	
	NRooks(const NRooks& nr);					
	NRooks& operator= (const NRooks& rhs);				
	virtual NRooks*	clone() const;			
	virtual ~NRooks();
		
private:		
	virtual void generate_samples(void);						
};