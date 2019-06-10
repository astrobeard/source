
#ifndef UTILS_H 
#define UTILS_H 

#ifndef max 
#define max(a, b) ({ \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a > _b ? _a : _b; \
}) 
#endif /* max */ 

#ifndef min 
#define min(a, b) ({ \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a < _b ? _a : _b; \
}) 
#endif /* min */ 

#ifndef LINESIZE 
#define LINESIZE 100000l 
#endif /* LINESIZE */ 

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
 * source: dataframe_utils.c 
 */ 
extern long long_sum(long *arr, long length); 

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
 * source: dataframe_utils.c 
 */ 
extern int int_sum(int *arr, long length); 

/* 
 * Obtain an array of (int) zeroes of a specified length. 
 * 
 * source: dataframe_utils.c 
 */ 
extern int *int_zeroes(long length); 

/* 
 * Obtain an array of (long) zeros of a specified length. 
 * 
 * header: utils.h 
 */ 
extern long *long_zeroes(long length); 

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
 * source: dataframe_utils.c 
 */ 
extern double *copy_double_ptr(double *arr, long length); 

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
 * source: dataframe_utils.c 
 */ 
extern long *range(long start, long stop); 

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
extern double ptr_min(double *arr, long length); 

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
extern double ptr_max(double *arr, long length); 

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
extern double ptr_sum(double *arr, long length); 

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
extern double ptr_mean(double *arr, long length); 

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
 * source: dataframe_utils.c 
 */ 
extern double ptr_median(double *arr, long length); 

/* 
 * Determines a measurement of the scatter in an array of doubles. Centered on 
 * the median, determines the lower and upper bounds that contain a given 
 * percentage of the data. 
 * 
 * Parameters 
 * ========== 
 * arr: 		A pointer to the data itself 
 * length: 		The number of points in the data set 
 * fraction: 	The fraction of the data contained within the lower and upper 
 * 				bounds. 
 * ptr: 		A 2-element pointer to put the scatter into 
 * 
 * Returns 
 * ======= 
 * Type *double :: The lower and upper bounds at returned[0] and returned[1], 
 * respectively. 
 * 
 * header: utils.h 
 */ 
extern void ptr_scatter(double *arr, long length, double fraction, 
	double *ptr); 

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
 * source: dataframe_utils.c 
 */ 
extern double ptr_quickselect(double *arr, long low, long high, long k); 

/* 
 * A classic quicksort function: sort an array of doubles in ascending order 
 * 
 * Parameters 
 * ========== 
 * arr: 			A pointer to the array to be sorted 
 * low: 			A starting index 
 * high: 			An ending index 
 * 
 * source: dataframe_utils.c 
 */ 
extern void ptr_quicksort(double *arr, long low, long high); 

#endif /* UTILS_H */ 


