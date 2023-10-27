#include <stdlib.h>
#include <math.h>
#include "utilities.h"

int randint(int a, int b){
	return (rand()%(b-a)+a);
}
double randDouble(double a, double b, int precision){
	int r = rand();
	double m = r%(int)((a-b)*pow(10, precision)) / pow(10, precision);
	return m + a;
}
int min2(int a, int b){
	return a<b ? a : b;
}
