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
extern double _sin(double x) { 

	return sin(x); 

}



