/* 
 * This is the header file for all of the calculus functions. 
 */ 

#ifndef CALCULUS_H 
#define CALCULUS_H 

#ifdef __cplusplus 
extern "C" {
#endif 

typedef struct mapped_function {

	/* 
	 * method:		The method of integration as a string 
	 * bins: 		The bin edges within which the function is evaluated 
	 * mapped: 		The values of f(x) in each bin 
	 * n: 			The number of bins in quadrature. This is always one less 
	 * 				than the length of the bins pointer array. 
	 */ 

	char *method; 
	double *bins; 
	double *mapped; 
	unsigned long n; 

} MAPPED_FUNCTION; 

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
extern double evaluate(MAPPED_FUNCTION f); 

#ifdef __cplusplus 
} 
#endif 

#endif /* CALCULUS_H */ 

