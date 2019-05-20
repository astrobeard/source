
#include <stdlib.h> 
#include "dataframe.h" 


/* 
 * Allocates memory for a dataframe struct and returns the pointer. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *dataframe_initialize(void) {

	/* Allocate memory and return the pointer */ 
	DATAFRAME *df = (DATAFRAME *) malloc (sizeof(DATAFRAME)); 
	return df; 

} 

/* 
 * Allocates memory for an array of dataframes and returns the pointer. 
 * 
 * Parameters 
 * ========== 
 * n: 		The number of dataframes to put in the array. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **dataframe_array_initialize(int n) {

	long i; 
	DATAFRAME **df = (DATAFRAME **) malloc (n * sizeof(DATAFRAME *)); 
	for (i = 0l; i < n; i++) {
		df[i] = (DATAFRAME *) malloc (sizeof(DATAFRAME)); 
	} 
	return df; 

}

/* 
 * Frees the memory storing both the data attribute and the dataframe struct 
 * itself. 
 * 
 * header: dataframe.h 
 */ 
extern void free_dataframe(DATAFRAME *df) {

	free(df -> data); 
	free(df); 

} 

/* 
 * Frees up the memory stored in an array of dataframes. 
 * 
 * Parameters 
 * ========== 
 * df: 		The array of dataframes to free up 
 * n: 		The number of dataframes in the array 
 * 
 * header: dataframe.h 
 */ 
extern void free_dataframe_array(DATAFRAME **df, int n) {

	int i; 
	for (i = 0; i < n; i++) {
		free(df[i] -> data); 
		free(df[i]); 
	}
	free(df); 

}

/* 
 * Determines the sum of an array of longs. 
 * 
 * Parameters 
 * ========== 
 * arr: 		A pointer to the array to sum 
 * length: 		The length of the array 
 * 
 * Returns 
 * ======= 
 * Type long: the sum of all elements. 
 * 
 * header: utils.h 
 */ 
extern long long_sum(long *arr, long length) {

	long i, sum = 0; /* Start at zero */ 
	for (i = 0l; i < length; i++) {
		sum += arr[i]; /* Add each element */ 
	}
	return sum; 

} 

/* 
 * Determines the sum of an array of ints. 
 * 
 * Parameters 
 * ========== 
 * arr: 		A pointer to the array to sum 
 * length: 		The length of the array 
 * 
 * Returns 
 * ======= 
 * Type int: the sum of all elements. 
 * 
 * header: utils.h 
 */ 
extern int int_sum(int *arr, long length) {

	long i; 
	int sum = 0; /* Start at zero */ 
	for (i = 0l; i < length; i++) {
		sum += arr[i]; /* Add each element */ 
	}
	return sum; 

} 

/* 
 * Obtain an array of (int) zeroes of a specified length. 
 * 
 * header: utils.h 
 */ 
extern int *int_zeroes(long length) {

	long i; 
	int *arr = (int *) malloc (length * sizeof(int)); 
	for (i = 0l; i < length; i++) {
		arr[i] = 0; 
	} 
	return arr; 

} 

/* 
 * Obtain an array of (long) zeros of a specified length. 
 * 
 * header: utils.h 
 */ 
extern long *long_zeroes(long length) {

	long i, *arr = (long *) malloc (length * sizeof(long)); 
	for (i = 0l; i < length; i++) {
		arr[i] = 0l; 
	} 
	return arr; 

} 

/* 
 * Copiese an array of doubles of a given length. 
 * 
 * Parameters 
 * ========== 
 * arr: 		The array to copy 
 * length: 		The length of the array 
 * 
 * Returns 
 * ======= 
 * A copy of the array in a different block of memory. 
 */ 
extern double *copy_double_ptr(double *arr, long length) {

	long i; 

	/* Allocate memory, copy each element, and then return */ 
	double *copy = (double *) malloc (length * sizeof(double)); 
	for (i = 0l; i < length; i++) {
		copy[i] = arr[i]; 
	} 
	return copy; 

}





