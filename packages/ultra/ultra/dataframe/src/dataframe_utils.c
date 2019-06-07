
#include <stdlib.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static void ptr_swap(double *arr, long i, long j); 

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
 * 
 * header: utils.h 
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
 * Emulates python's range function by taking in a start and a stop and 
 * returning an array from start to stop - 1l (inclusive) 
 * 
 * Parameters 
 * ========== 
 * start: 		The starting value 
 * stop: 		The stopping value 
 * 
 * Returns 
 * ======= 
 * Type *long :: The resultant array from start to stop - 1l 
 * 
 * header: utils.h 
 */ 
extern long *range(long start, long stop) {

	long i, *arr = (long *) malloc ((stop - start) * sizeof(long)); 
	for (i = 0l; i < stop - start; i++) {
		arr[i] = i; 
	} 
	return arr; 

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

/* 
 * Find the median of an array stored in a double pointer.  
 * 
 * Parameters 
 * ========== 
 * arr: 		A pointer to the array itself 
 * length: 		The number of elements stored in the array 
 * 
 * Returns 
 * ======= 
 * The median value of the double pointer 
 * 
 * header: utils.h 
 */ 
extern double ptr_median(double *arr, long length) {

	/* The index and value stored at the center of the array */ 
	long middle = length / 2; 
	double x = arr[middle]; 

	/* Start scans from the left and right */ 
	long i = 0, j = length - 1l; 
	do {
		while (arr[i] < x) { 
			/* 
			 * From the left, increment i up until we find a value larger 
			 * than x. 
			 */ 
			i++; 
		} 
		while (arr[j] > x) { 
			/* 
			 * From the right, increment j down until we find a value smaller 
			 * than x. 
			 */ 
			j--; 
		} 
		/* Swap the values and keep going */ 
		double t = arr[i]; 
		arr[i] = arr[j]; 
		arr[j] = t; 
	} while (i < j); 

	/* 
	 * i and j have now met in the middle and are adjacent. Half of the values 
	 * are above them and half of them are below them. 
	 * 
	 * If there is an even number of elements, the median is the mean of a[i] 
	 * and a[j]. If not, it is a[i]. 
	 */ 
	if (length % 2l == 0l) {
		return (arr[i] + arr[j]) / 2; 
	} else {
		return arr[i]; 
	}

}

/* 
 * Sorts a double pointer array from least to greatest. 
 *  
 * Parameters 
 * ========== 
 * arr: 		The array to sort 
 * length: 		The length of the array 
 * 
 * Returns 
 * ======= 
 * Type *double :: The sorted array, which will have the same length 
 * 
 * header: utils.h 
 */ 
extern double *ptr_sort(double *arr, long length) {

	/* Run the operations on a copy of the array */ 
	long i, j; 
	double *sorted = copy_double_ptr(arr, length); 

	for (i = 0l; i < length - 1; i++) { 
		/* 
		 * Look at each subsequent element of the array and find the smallest 
		 * one. Then swap the minimum for the current position.  
		 */ 
		long smallest = i; 
		for (j = i + 1l; j < length; j++) {
			if (sorted[j] <= sorted[smallest]) {
				smallest = j; 
			} else {
				continue; 
			}
		} 
		ptr_swap(sorted, i, smallest); 
	} 
	/* The largest element will naturally fall into the last position */ 
	return sorted; 

} 

/* 
 * Swap the i'th and j'th elements of a double pointer array 
 * 
 * Parameters 
 * ========== 
 * arr: 		The double pointer array itself 
 * i: 			The first index 
 * j: 			The second index 
 */ 
static void ptr_swap(double *arr, long i, long j) {

	double x = arr[i]; 
	double y = arr[j]; 
	arr[i] = y; 
	arr[j] = x; 

}






