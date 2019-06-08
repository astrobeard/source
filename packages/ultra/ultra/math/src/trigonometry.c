/* 
 * The source code for the trigonometry functions in ultra's math library 
 */ 

#include <stdlib.h> 
#include <math.h> 
#include "ultramath.h" 
#include "utils.h" 

/* ---------- Static Function Comment Headers Not Duplicated Here ---------- */ 

/* 
 * Determine the value of x! (x factorial), where 
 * x! = 1 (x = 0) 
 * 		x * (x - 1)! (x > 0) 
 * 
 * Parameters 
 * ========== 
 * x: 			A long integer to compute the factorial of 
 * 
 * Returns 
 * ======= 
 * The value of x!; -1l if x < 0 
 * 
 * header: ultramath.h 
 */ 
extern long _factorial(long x) {

	if (x == 0l) { 
		return 1l; 
	} else if (x < 0l) { 
		return -1l; 
	} else {
		return x * _factorial(x - 1l); 
	}

}

/* 
 * Compute the sine of x to specified precision 
 * 
 * Parameters 
 * ========== 
 * x: 				The value to compute the sine of 
 * tolerance: 		The specified tolerance 
 * 
 * Returns 
 * ======= 
 * A 3-element double pointer 
 * returned[0]: The numerically determined sin(x) 
 * returned[1]: The estimated fractional error 
 * returned[1]: The number of iterations 
 * 
 * header: ultramath.h 
 */ 
extern double *_sin(double x, double tolerance) { 

	long n = 1l; 
	double new_sin_x = x, old_sin_x, error; 

	do {
		old_sin_x = new_sin_x; 

		if (n % 2l) {
			new_sin_x -= pow(x, 2l * n + 1l) / _factorial(2l * n + 1l); 
		} else {
			new_sin_x += pow(x, 2l * n + 1l) / _factorial(2l * n + 1l); 
		} 
		error = _absval(old_sin_x / new_sin_x - 1); 
		n++; 

	} while (error >= tolerance && n < MAX_ITERS); 

	double *results = (double *) malloc (3 * sizeof(double)); 
	results[0] = new_sin_x; 
	results[1] = error; 
	results[2] = n; 
	return results; 

}



