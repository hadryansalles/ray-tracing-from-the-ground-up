#pragma once

inline float max(float x0, float x1) {
	return((x0 > x1) ? x0 : x1);
}

inline float min(float a, float b){
	return (a < b)? a : b;
}

inline float rand_float(){
	return (float) rand()/RAND_MAX;
}

inline int rand_int(){
	return (int) rand();
}

inline float clamp(float x, float min, float max){
	return (x < min ? min : (x > max ? max : x));
}