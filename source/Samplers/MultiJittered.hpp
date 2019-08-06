#pragma once
#include "Sampler.hpp"

class MultiJittered: public Sampler {
public:
	MultiJittered(const int num_samples = 1, const int m = 50);
	MultiJittered(const MultiJittered& rhs);		
	MultiJittered& operator= (const MultiJittered& rhs);				
	virtual MultiJittered* clone() const;		
	virtual ~MultiJittered();								
		
private:
	virtual void generate_samples();		
};