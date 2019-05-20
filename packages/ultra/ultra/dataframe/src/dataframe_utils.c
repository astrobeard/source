
#include <stdlib.h> 
#include "dataframe.h" 
#include "utils.h" 


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

/* 
 * Finds the minimum value in a double pointer array  
 * 
 * Parameters 
 * ========== 
 * arr: 		The pointer itself 
 * length: 		The length of the pointer 
 * 
 * Returns 
 * ======= 
 * The minimum value in the array. 
 * (0 if length <= 0) 
 * 
 * header: utils.h 
 */ 
extern double ptr_min(double *arr, long length) {

	if (length <= 0l) {
		return 0; /* Return zero if there isn't any data */ 
	} else if (length == 1l) {
		return arr[0]; /* There's only one data point */ 
	} else { 
		/* Else look through each value and bookkeep the minimum */ 
		long i; 
		double minimum = min(arr[0], arr[1]); 
		for (i = 2l; i < length; i++) {
			minimum = min(minimum, arr[i]); 
		} 
		return minimum; 
	} 
} 

/* 
 * Finds the maximum value in a double pointer array 
 * 
 * Parameters
 * ========== 
 * arr: 		The pointer itself 
 * length: 		The length of the pointer 
 * 
 * Returns 
 * ======= 
 * The maximum value in the array. 
 * (0 if length <= 0) 
 * 
 * header: utils.h 
 */ 
extern double ptr_max(double *arr, long length) {

	if (length <= 0l) {
		return 0; /* Return 0 if there isn't any data */ 
	} else if (length == 1l) {
		return arr[0]; /* There's only one data point */ 
	} else { 
		/* Else look through each value and bookkeep the maximum */ 
		long i; 
		double maximum = max(arr[0], arr[1]); 
		for (i = 2l; i < length; i++) {
			maximum = max(maximum, arr[i]); 
		} 
		return maximum; 
	}

} 

/* 
 * Determines the sum of a double pointer array 
 * 
 * Parameters 
 * ========== 
 * arr: 		The pointer itself 
 * length: 		The length of the pointer 
 * 
 * Returns 
 * ======= 
 * The sum of the all values in the array 
 * 
 * header: utils.h 
 */ 
extern double ptr_sum(double *arr, long length) {

	long i; 
	double sum = 0; /* Start at 0 */ 
	for (i = 0l; i < length; i++) {
		sum += arr[i]; /* Add each element and return */ 
	} 
	return sum; 

}

/* 
 * Determines the arithmetic mean of a double pointer array 
 * 
 * Parameters 
 * ========== 
 * arr: 		The array itself 
 * length: 		The length of the double pointer array 
 * 
 * Returns 
 * ======= 
 * The arithmetic mean of the array 
 * (0 if there isn't any data) 
 * 
 * header: utils.h 
 */ 
extern double ptr_mean(double *arr, long length) {

	if (length <= 0l) {
		return 0; /* Return 0 if there isn't any data */ 
	} else if (length == 1l) {
		return arr[0]; /* There's only one data point */ 
	} else {
		/* Else add all of them up and divide by length */ 
		return ptr_sum(arr, length) / length; 
	}

}





