
#ifndef UTILS_H 
#define UTILS_H 

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

#endif /* UTILS_H */ 


