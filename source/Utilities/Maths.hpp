#pragma once

double max(double x0, double x1) {
	return((x0 > x1) ? x0 : x1);
}

float rand_float(){
	return (float) rand()/RAND_MAX;
}