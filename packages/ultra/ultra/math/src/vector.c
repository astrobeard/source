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

/* 
 * Obtain a VECTOR struct corresponding to a unit vector pointing in the same 
 * direction as another vector v. 
 * 
 * Parameters 
 * ========== 
 * v: 		The vector itself 
 * 
 * Returns 
 * ======= 
 * Type VECTOR *: A pointer to the VECTOR struct containing the unit vector; 
 * NULL if the vector is a NULL pointer 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_direction(VECTOR v) {

	int i; 
	double norm = vector_magnitude(v); 
	VECTOR *new = vector_initialize(); 
	if (new == NULL) return NULL; 
	vector_set_dimension(new, v.dimension); 
	for (i = 0; i < v.dimension; i++) {
		new -> vector[i] = v.vector[i] / norm; 
	} 
	return new; 

} 

/* 
 * Performs vector scalar multiplication. 
 * 
 * Parameters 
 * ========== 
 * v: 			The vector to multiply the scalar through 
 * scalar: 		The scalar itself (how crazy is that) 
 * 
 * Returns 
 * ======= 
 * A new vector object, whose componenets have been multiplied by the 
 * scalar 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_scalar_multiplication(VECTOR v, double scalar) {

	int i; 
	VECTOR *new = vector_initialize(); 
	if (new == NULL) return NULL; 
	vector_set_dimension(new, v.dimension); 
	for (i = 0; i < v.dimension; i++) {
		new -> vector[i] = scalar * v.vector[i]; 
	} 
	return new; 

}

/* 
 * Implements vector addition. 
 * 
 * Parameters 
 * ========== 
 * v1: 		The first vector 
 * v2: 		The second vector 
 * 
 * Returns 
 * ======= 
 * The resultant vector that arises from v1 + v2; NULL if the v1 
 * and v2 do not have the same dimensionality, or instantiation of 
 * a new vector fails. 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_addition(VECTOR v1, VECTOR v2) {

	if (v1.dimension != v2.dimension) {
		return NULL; 
	} else {
		int i; 
		VECTOR *new = vector_initialize(); 
		if (new == NULL) return NULL; 
		vector_set_dimension(new, v1.dimension); 
		for (i = 0; i < v1.dimension; i++) {
			new -> vector[i] = v1.vector[i] + v2.vector[i]; 
		} 
		return new; 
	}

} 

/* 
 * Return the dot product of two vectors 
 * 
 * Parameters 
 * ========== 
 * v1: 			The first vector 
 * v2: 			The second vector 
 * 
 * Returns 
 * ======= 
 * The dot product of the two vectors; 0 if they are not of the same dimension 
 * 
 * header: vector.h 
 */ 
extern double vector_dot_product(VECTOR v1, VECTOR v2) {

	if (v1.dimension != v2.dimension) {
		return 0; 
	} else {
		int i; 
		double x = 0; 
		for (i = 0; i < v1.dimension; i++) { 
			x += v1.vector[i] * v2.vector[i]; 
		} 
		return x; 
	}

} 

/* 
 * Determine the cross product of two vectors. 
 * 
 * Parameters 
 * ========== 
 * v1: 		The first vector 
 * v2: 		The second vector 
 * 
 * Returns 
 * ======= 
 * The vector representing the cross product v1 x v2 in that order 
 * NULL if either vector is not 3-dimensional 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_cross_product(VECTOR v1, VECTOR v2) {

	if (v1.dimension != 3 && v2.dimension != 3) {
		return NULL; 
	} else {
		VECTOR *new = vector_initialize(); 
		vector_set_dimension(new, 3); 
		new -> vector[0] = (v1.vector[1] * v2.vector[2] - 
			v1.vector[2] * v2.vector[1]); 
		new -> vector[1] = (v1.vector[2] * v2.vector[0] - 
			v1.vector[0] * v2.vector[2]); 
		new -> vector[2] = (v1.vector[0] * v2.vector[1] - 
			v1.vector[1] * v2.vector[0]); 
		return new; 
	}

}



