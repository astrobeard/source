/* 
 * This is a simple script used for testing new mathematical functions. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "vector.h" 

int main(void) {

	VECTOR *v = vector_initialize(); 
	vector_set_dimension(v, 3); 
	v -> vector[0] = 1; 
	v -> vector[1] = 2; 
	v -> vector[2] = 3; 

	printf("Magnitude of vector: %lf\n", vector_magnitude(*v)); 

	vector_free(v); 
	return 0; 

}

