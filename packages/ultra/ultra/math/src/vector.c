/* 
 * This is the source code for the vector functions implemented in C. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "vector.h" 

/* 
 * Allocates memory for a vector object and returns a pointer to it 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_initialize(void) { 

	return (VECTOR *) malloc (sizeof(VECTOR)); 

} 

/* 
 * Frees the memory stored within a vector object 
 * 
 * Parameters 
 * ========== 
 * v: 			A pointer to the vector to free 
 * 
 * header: vector.h 
 */ 
extern void vector_free(VECTOR *v) {

	free(v -> vector); 
	free(v); 

} 

/* 
 * Set the dimensionality of the vector, allocating memory for the vector 
 * array itself simultaneously. 
 * 
 * Parameters 
 * ========== 
 * v: 			A pointer to the vector itself 
 * d: 			The dimensionality of the vector 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure (if d <= 0) 
 * 
 * header: vector.h 
 */ 
extern int vector_set_dimension(VECTOR *v, int d) {

	if (d <= 0) {
		return 1; 
	} else {
		v -> dimension = d; 
		v -> vector = (double *) malloc (d * sizeof(double)); 
		return 0; 
	}

} 

/* 
 * Set the vector associated with the vector struct. This routine assumes that 
 * vector_set_dimension has already been called on this vector, such that the 
 * dimension is known, and that the double pointer that is passed is of the 
 * correct dimensionality. 
 * 
 * Parameters 
 * ========== 
 * v: 		A pointer to the vector struct itself 
 * arr: 	A double pointer to an array to adopt as the vector 
 * 
 * Returns 
 * ======= 
 * 0 on success, anything else would be a SystemError at the python level 
 * 
 * Notes 
 * ===== 
 * This routine copies over each element of the double array rather than 
 * adopting the pointer. 
 * 
 * header: vector.h 
 */ 
extern int vector_set_vector(VECTOR *v, double *arr) {

	int i; 
	for (i = 0; i < (*v).dimension; i++) {
		v -> vector[i] = arr[i]; 
	} 
	return 0; 

}

/* 
 * Determine the magnitude of the vector. This is determined according to the 
 * mathematical format of the square root of the norm-squared. 
 * 
 * Parameters 
 * ========== 
 * v: 			The vector itself 
 * 
 * Returns
 * ======= 
 * The square root of the sum of the components of the vector squared. 
 * 
 * header: vector.h 
 */ 
extern double vector_magnitude(VECTOR v) {

	int i; 
	double norm_squared = 0; 
	for (i = 0; i < v.dimension; i++) {
		/* Incrementally add the square of each component of the vector */ 
		norm_squared += v.vector[i] * v.vector[i]; 
	} 
	/* Return the square root */ 
	return sqrt(norm_squared); 

} 



