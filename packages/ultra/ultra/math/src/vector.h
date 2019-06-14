/* 
 * This is the header file for the vector functions implemented in C. 
 */ 

#ifndef VECTOR_H 
#define VECTOR_H 

#ifdef __cplusplus 
extern "C" {
#endif 

typedef struct vector {

	/* 
	 * The Vector Struct 
	 * ================= 
	 * vector: 		The vector itself 
	 * dimension: 	The dimensionality of the vector 
	 */ 

	double *vector; 
	int dimension; 

} VECTOR; 

/* 
 * Allocates memory for a vector object and returns a pointer to it 
 * 
 * source: vector.c 
 */ 
extern VECTOR *vector_initialize(void); 

/* 
 * Frees the memory stored within a vector object 
 * 
 * Parameters 
 * ========== 
 * v: 			A pointer to the vector to free 
 * 
 * source: vector.c 
 */ 
extern void vector_free(VECTOR *v); 

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
extern int vector_set_dimension(VECTOR *v, int d); 

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
extern int vector_set_vector(VECTOR *v, double *arr); 

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
 * source: vector.c 
 */ 
extern double vector_magnitude(VECTOR v); 

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
 * Type VECTOR *: A pointer to the VECTOR struct containing the unit vector 
 * 
 * header: vector.h 
 */ 
extern VECTOR *vector_direction(VECTOR v); 

#ifdef __cplusplus
} 
#endif 

#endif /* VECTOR_H */ 


