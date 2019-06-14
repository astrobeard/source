/* 
 * This is a simple script used for testing new mathematical functions. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "vector.h" 

int main(void) {

	VECTOR *v1 = vector_initialize(); 
	VECTOR *v2 = vector_initialize(); 

	vector_set_dimension(v1, 3); 
	vector_set_dimension(v2, 3); 

	v1 -> vector[0] = 1; 
	v1 -> vector[1] = 2; 
	v1 -> vector[2] = 3; 
	v2 -> vector[0] = 2; 
	v2 -> vector[1] = 3; 
	v2 -> vector[2] = 4; 

	double x = vector_dot_product(*v1, *v2); 
	printf("Dot product = %lf\n", x); 

	vector_free(v1); 
	vector_free(v2); 
	return 0; 

}

