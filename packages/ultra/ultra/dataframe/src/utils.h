
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
 */ 
extern double *copy_double_ptr(double *arr, long length); 

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
extern double *ptr_sort(double *arr, long length); 

#endif /* UTILS_H */ 


