
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static long get_bin_number(double value, double *binspace, long num_bins); 
static long *rank_indeces(DATAFRAME df, int column); 
static void long_ptr_swap(long *arr, long i, long j); 
static void double_ptr_swap(double *arr, long i, long j); 

/* 
 * Sorts the data from least to greatest based on the values in a given 
 * column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to take the index of 
 * 
 * Returns 
 * ======= 
 * Type DATAFRAME :: A new dataframe with the same rows, but sorted least to 
 * greatest according to the column'th value in each row. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *dfcolumn_order(DATAFRAME df, int column) {

	int j; 
	long i, *indeces = rank_indeces(df, column); 
	DATAFRAME *new = dataframe_initialize(); 
	new -> num_rows = df.num_rows; 
	new -> num_cols = df.num_cols; 
	new -> data = (double **) malloc (df.num_rows * sizeof(double *)); 
	for (i = 0l; i < df.num_rows; i++) {
		new -> data[i] = (double *) malloc (df.num_cols * sizeof(double)); 
		for (j = 0; j < df.num_cols; j++) {
			new -> data[i][j] = df.data[indeces[i]][j]; 
		} 
	} 
	free(indeces); 
	return new; 

} 

/* 
 * Determine the number of rows that fall within specified bins (i.e. a 
 * histogram) based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to get counts based on 
 * binspace: 	The binspace to sort based on 
 * num_bins: 	The number of bins in the binspace. This should be one less 
 * 				than the number of values in the binspace array. 
 * 
 * Returns 
 * ======= 
 * Type *long :: The counts within each bin 
 * 
 * header: dataframe.h 
 */ 
extern long *hist(DATAFRAME df, int column, double *binspace, long num_bins) {

	long i, *counts = (long *) malloc (num_bins * sizeof(long)); 
	for (i = 0l; i < df.num_rows; i++) {
		long bin = get_bin_number(df.data[i][column], binspace, num_bins); 
		if (bin != -1l) {
			counts[bin]++; 
		} else {
			continue; 
		} 
	} 
	return counts; 

}

/* 
 * Determines the bin number of a given value within a specified binspace. 
 * 
 * Parameters 
 * ========== 
 * value: 		The value to get the bin number for 
 * binspace: 	The bin edges 
 * num_bins: 	The number of bins. This should be one less than the number of 
 * 				values in the binspace array. 
 * 
 * Returns 
 * ======= 
 * Type long :: The bin value itself 
 */ 
static long get_bin_number(double value, double *binspace, long num_bins) {

	long i; 
	for (i = 0l; i < num_bins; i++) {
		/* If the value is between two bin edges */ 
		if (binspace[i] <= value && value <= binspace[i + 1l]) {
			return i; 
		} else {
			continue; 
		} 
	} 
	/* The value is not within the binspace. Return -1l on failure. */ 
	return -1l; 

}

static long *rank_indeces(DATAFRAME df, int column) {

	/* Run the operations on a copy of the indeces */ 
	long i, j, *indeces = range(0, df.num_rows); 
	double *col = dfcolumn(df, column); /* Pull a copy, this is faster */ 

	for (i = 0l; i < df.num_rows; i++) {
		/* 
		 * Look the column'th element of each subsequent row and find the 
		 * smallest index. Then swap the indeces. 
		 */ 
		long smallest = i; 
		for (j = i + 1l; j < df.num_rows; j++) {
			if (col[j] <= col[smallest]) {
				smallest = j; 
			} else {
				continue; 
			}
		} 
		double_ptr_swap(col, i, smallest); 
		long_ptr_swap(indeces, i, smallest); 
		printf("\r%ld of %ld", i, df.num_rows); 
	} 
	printf("\n"); 
	return indeces; 

} 

/* 
 * Swap the i'th and j'th elements of a long pointer array 
 * 
 * Parameters 
 * ========== 
 * arr: 		The long pointer array itself 
 * i: 			The first index 
 * j: 			The second index 
 */ 
static void long_ptr_swap(long *arr, long i, long j) {

	long x = arr[i]; 
	long y = arr[j]; 
	arr[i] = y; 
	arr[j] = x; 

} 

static void double_ptr_swap(double *arr, long i, long j) {

	double x = arr[i]; 
	double y = arr[j]; 
	arr[i] = y; 
	arr[j] = x; 

}


