#pragma once

inline double max(double x0, double x1) {
	return((x0 > x1) ? x0 : x1);
}

inline float rand_float(){
	return (float) rand()/RAND_MAX;
}

inline int rand_int(){
	return (int) rand();
}