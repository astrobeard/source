
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <time.h> 
#include "dataframe.h" 
#include "utils.h" 

/* 
 * Currently running tests on quicksort. 
 */ 
int main(void) { 

	srand(time(NULL)); 
	long i; 
	double *arr = (double *) malloc (10 * sizeof(double)); 

	for (i = 0l; i < 10l; i++) {
		arr[i] = 100 * (double) rand() / (double) RAND_MAX;  
	} 

	for (i = 0l; i < 10l; i++) {
		printf("arr[%ld] = %lf\n", i, arr[i]); 
	} 

	for (i = 0l; i < 10l; i++) {
		printf("quickselect(%ld) = %lf\n", i, ptr_quickselect(arr, 0, 9, i)); 
	}

	printf("Sorting....\n"); 
	ptr_quicksort(arr, 0, 9); 

	for (i = 0l; i < 10l; i++) {
		printf("arr[%ld] = %lf\n", i, arr[i]); 
	} 

	return 0; 

}


