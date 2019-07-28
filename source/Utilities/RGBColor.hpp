#pragma once

#include <math.h>

class RGBColor {	
public:
	float r; 
	float g; 
	float b;									
				
public:	
	RGBColor();
	RGBColor(float c);
	RGBColor(float r, float g, float b);
	RGBColor(const RGBColor& c);
	~RGBColor();

	RGBColor& operator= (const RGBColor& rhs);		// assignment operator
	RGBColor operator+ (const RGBColor& c) const;	// addition
	RGBColor& operator+= (const RGBColor& c);		// compound addition
	RGBColor operator* (const float a) const;		// multiplication by a float on the right
	RGBColor& operator*= (const float a);			// compound multiplication by a float on the right
	RGBColor operator/ (const float a) const;		// division by a float
	RGBColor& operator/= (const float a); 			// compound division by a float
	RGBColor operator* (const RGBColor& c) const; 	// component-wise multiplication
	bool operator== (const RGBColor& c) const;		// are two RGBColours the same?
	RGBColor powc(float p) const;					// raise components to a power
	float average(void) const;						// the average of the components
};