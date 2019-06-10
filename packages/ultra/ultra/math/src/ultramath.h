/* 
 * This is the header file for all of the ultra math functions 
 */ 

#ifndef ULTRAMATH_H 
#define ULTRAMATH_H 

/* 
 * PI: 				The value of pi  
 * EE: 				The value of Euler's number 
 */ 
#ifndef _PI
#define _PI 3.14159265358979 
#endif /* PI */ 
#ifndef _EE
#define _EE 2.71828182845905 
#endif /* EE */ 

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
// extern long factorial(long x); 

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
extern double _sin(double x); 



#endif /* ULTRAMATH_H */ 


