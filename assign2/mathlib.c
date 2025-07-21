#include <stdio.h>
#include <math.h>
#include "mathlib.h"

double acc = 0.001;
double pie = 3.1415926535897932384626433832795;
double arcSin(double x){
	double y = 0;
	double y1 = x;
	while (fabs(y1-y) > acc){
		y = y1;
		y1 = y-(sin(y)-x)/cos(y);
	}
	return y1;
}

double arcCos(double x){
	return(((pie/2)-arcSin(x)));
}
double arcTan(double x){
	return arcSin(x/(sqrt(x*x)+1));
}

double Log(double x){
	double y = 0;
	double y1=x;
	while (fabs(y1-y) > acc){
		y=y1;
		y1=y + ((x-exp(y))/exp(y));
	}
	return y1;
}
