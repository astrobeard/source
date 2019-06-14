/* 
 * This is the source code for numerical integration of user-defined functions 
 * in the ultra math module. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "calculus.h" 

static double midpt(MAPPED_FUNCTION f); 
static double euler(MAPPED_FUNCTION f); 
static double trapzd(MAPPED_FUNCTION f); 

/* 
 * Evaluate the integral for the current number of bins and specified method 
 * of integration. 
 * 
 * Parameters 
 * ========== 
 * f: 			The MAPPED_FUNCTION struct associated with the integral 
 * 
 * Returns 
 * ======= 
 * The approximated value of the integral for the specified method and current 
 * number of bins 
 */ 
extern double evaluate(MAPPED_FUNCTION f) {

	if (!strcmp(f.method, "euler")) {
		return euler(f); 
	} else if (!strcmp(f.method, "midpt")) {
		return midpt(f); 
	} else if (!strcmp(f.method, "trapzd")) {
		return trapzd(f); 
	} else {
		printf("Internal Error.\n"); 
		exit(0); 
	} 

}

/* 
 * Evaluate the integral according to trapezoid rule. The function will have 
 * already been evaluated the edges of each bin. Trapezoid rule approximates 
 * the integral as the sum of the areas of individual trapezoids bound by 
 * the x-axis and the value of the function at neighboring bin edges. 
 * 
 * Parameters 
 * ========== 
 * f: 			The MAPPED_FUNCTION struct associated with the integral 
 * 
 * Returns 
 * ======= 
 * The approximated value of the integral for the current number of bins 
 */ 
static double trapzd(MAPPED_FUNCTION f) {

	double x = 0; /* Store the value of the integral here */ 

	unsigned long i; 
	for (i = 0l; i < f.n; i++) { 
		/* 
		 * Under trapezoid rule, the function is evaluated at all bin edges. 
		 * Incrementally add twice the area of a trapezoid to the value of x. 
		 */ 
		x += (f.mapped[i + 1l] + f.mapped[i]) * (f.bins[i + 1l] - f.bins[i]); 
	} 

	return 0.5 * x; /* Propogate the factor of 1/2 through */ 

}

/* 
 * Evaluate the integral according to midpoint rule. The function will have 
 * already been evaluated at the center of each bin. Midpoint rule approximates 
 * the integral as the sum of these values times the area of each bin. 
 * 
 * Parameters 
 * ========== 
 * f: 			The MAPPED_FUNCTION struct associated with this integral 
 * 
 * Returns 
 * ======= 
 * The approximated value of the integral for the current number of bins 
 */ 
static double midpt(MAPPED_FUNCTION f) {

	/* 
	 * The only difference between Euler's method and midpoint rule is where 
	 * the function is evaluated. This will be handled before this function 
	 * is called, and the area under the curve according to midpoint rule will 
	 * be determined in exactly the same manner as with Euler's method. 
	 */ 
	return euler(f); 

}

/* 
 * Evaluate the integral according to Euler's method. The function will have 
 * already been evaluated at the left edge of each bin. Euler's method 
 * approximates the integral as the sum of these values times the area of each 
 * bin. 
 * 
 * Parameters 
 * ========== 
 * f: 			The MAPPED_FUNCTION struct associated with the integral 
 * 
 * Returns 
 * =======
 * The approximated value of the integral for the current number of bins 
 */ 
static double euler(MAPPED_FUNCTION f) {

	double x = 0; /* Store the value of the integral here */ 

	unsigned long i; 
	for (i = 0l; i < f.n; i++) {
		/* 
		 * For each bin within which the function is evaluated, multiply it by 
		 * the difference to the next bin and add it incrementally to x 
		 */ 
		x += f.mapped[i] * (f.bins[i + 1l] - f.bins[i]); 
	} 

	return x; /* Return the total */ 

}


