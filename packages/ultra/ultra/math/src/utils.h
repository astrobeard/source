/* 
 * This is the header file for ultramath utility functions 
 */ 

#ifndef UTILS_H 
#define UTILS_H 

/* 
 * MAX_ITERS: 		The maximum number of iterations in recursive functions 
 * TOLERANCE: 		The allowed numerical tolerance of all calculations 
 */ 
#ifndef MAX_ITERS 
#define MAX_ITERS 2e8 
#endif /* MAX_ITERS */ 
#ifndef TOLERANCE 
#define TOLERANCE 1e-12 
#endif 

/* 
 * Determine the absolute value of x 
 * 
 * Parameters 
 * ========== 
 * x: 		The value itself 
 * 
 * Returns 
 * ======= 
 * sign(x) * x 
 * 
 * source: utils.c 
 */ 
extern double _absval(double x); 

/* 
 * Determine the sign of a double 
 * 
 * Parameters 
 * ========== 
 * x: 		The value itself 
 * 
 * Returns 
 * ======= 
 * 1 if x >= 0, -1 otherwise 
 * 
 * source: utils.c 
 */ 
extern int _sign(double x); 

#endif /* UTILS_H */ 
