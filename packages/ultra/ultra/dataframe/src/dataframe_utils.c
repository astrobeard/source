
#include <stdlib.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static long partition(double *arr, long low, long high); 
static void swap(double *a, double *b); 

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

	if (length % 2l == 0l) {
		/* 
		 * If there are an even number of elements, the median is the mean of 
		 * the two in the middle. 
		 */ 
		return (ptr_quickselect(arr, 0, length - 1l, length / 2l - 1l) + 
			ptr_quickselect(arr, 0, length - 1l, length / 2l)) / 2; 
	} else {
		return ptr_quickselect(arr, 0, length - 1l, length / 2l); 
	}

}

/* 
 * A classic quickselect function: determine the kth smallest element in an 
 * array of unsorted values. 
 * 
 * Parameters 
 * ========== 
 * arr: 		A pointer to the array of unsorted values 
 * low: 		A starting index 
 * high: 		An ending index 
 * k: 			The rank order of the element to take 
 * 
 * Returns 
 * ======= 
 * The kth smallest element in the array 
 * 
 * header: utils.h 
 */ 
extern double ptr_quickselect(double *arr, long low, long high, long k) {

	if (low == high) {
		/* The list contains only one element, return that */ 
		return arr[low]; 
	} else { 
		/* 
		 * Start by moving the final element into proper position as in the 
		 * traditional quicksort algorithm. Then sort only above or below the 
		 * partition as needed. 
		 */ 
		long p = partition(arr, low, high); 
		if (k == p) { 
			/* arr[k] is the proper value, return */ 
			return arr[k]; 
		} else if (k < p) { 
			/* 
			 * arr[k] lies below arr[p]. Sort the values less than arr[p] by 
			 * recursively calling this function. 
			 */ 
			return ptr_quickselect(arr, low, p - 1l, k); 
		} else { 
			/* 
			 * arr[k] lies above arr[p]. Sort the values greather than arr[p] 
			 * by recursively calling this function. 
			 */ 
			return ptr_quickselect(arr, p + 1l, high, k); 
		} 
	} 

}

/* 
 * A classic quicksort function: sort an array of doubles in ascending order 
 * 
 * Parameters 
 * ========== 
 * arr: 			A pointer to the array to be sorted 
 * low: 			A starting index 
 * high: 			An ending index 
 * 
 * header: utils.h 
 */ 
extern void ptr_quicksort(double *arr, long low, long high) {

	if (low < high) { 
		/* 
		 * The function terminates when low < high is no longer satisfied. 
		 * Start by moving the final element to its proper position. Then 
		 * recursively sort each piece of the array until the whole thing is 
		 * in ascending order. 
		 */ 
		long p = partition(arr, low, high); 
		ptr_quicksort(arr, low, p - 1l); 
		ptr_quicksort(arr, p + 1l, high); 

	} else {} 

} 

/* 
 * A classic partition function: sort an array according to a given value such 
 * that all values less than this occur before that value in the array. By 
 * extension, all values greater than this value will occur after it. 
 * 
 * Parameters 
 * ========== 
 * arr: 			A pointer to the array to be partitioned 
 * low: 			The starting index 
 * high: 			The index of the value to be partitioned on 
 * 
 * Returns 
 * ======= 
 * The index of the value to be partitioned on following sorting 
 */ 
static long partition(double *arr, long low, long high) {

	double pivot = arr[high]; /* The value to partition on */ 
	long j, i = low - 1l; /* Start one below low */ 

	for (j = low; j < high; j++) {  
		if (arr[j] <= pivot) { 
			/* 
			 * arr[j] is smaller than the pivot -> move it to the beginning of 
			 * the array. Increment i up by 1 to not overwrite any data 
			 */ 
			i++; 
			swap(&arr[i], &arr[j]); 
		} else {
			continue; 
		} 
	} 

	/* 
	 * Move arr[high] to the next position after element i. All elements 
	 * before this are less than the pivot. 
	 */ 
	swap(&arr[i + 1l], &arr[high]); 
	return i + 1l; 

}

/* 
 * Swaps the values stored in two doubles 
 * 
 * Parameters 
 * ========== 
 * a: 			A pointer to the first double 
 * b: 			A pointer to the second double 
 */ 
static void swap(double *a, double *b) {

	double x = *a; 
	*a = *b; 
	*b = x; 

} 



