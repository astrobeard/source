
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
 * Splits the data into equal number bins based on the data in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column number to sort based on 
 * num_subs:	The number of subsamples to take 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **equal_number_samples(DATAFRAME df, int column, 
	long num_subs) {

	/* For-looping */ 
	long i, j; 
	int k; 

	/* First sort the data from least to greatest */ 
	DATAFRAME *ordered = dfcolumn_order(df, column); 

	/* 
	 * The number of points in each sample. This prescription will inevitably 
	 * lose some data at the high-number end of this column, but all the 
	 * functions in this packages are meant to deal with large datasets 
	 * anyway. 
	 * 
	 * Allocate memory for each subsamples data and copy it over directly. 
	 */ 
	long x = (long) (df.num_rows / num_subs); 
	DATAFRAME **samples = dataframe_array_initialize(num_subs); 
	for (i = 0l; i < num_subs; i++) {
		samples[i] -> num_rows = x; 
		samples[i] -> num_cols = df.num_cols; 
		samples[i] -> data = (double **) malloc (x * sizeof(double *)); 
		for (j = 0l; j < x; j++) {
			samples[i] -> data[j] = (double *) malloc (df.num_cols * 
				sizeof(double)); 
			for (k = 0; k < df.num_cols; k++) {
				samples[i] -> data[j][k] = (*ordered).data[j * i][k]; 
			}
		}
	} 

	/* Free the ordered data and return */ 
	free(ordered); 
	return samples; 

} 

/* 
 * Sorts the dataframe based into bins based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column number to sort based on 
 * binspace: 	The bin-edges to sort with 
 * num_bins: 	The number of bins. This should always be one less than the 
 * 				number of elements in the binspace array. 
 * 
 * Returns 
 * ======= 
 * Type **DATAFRAME :: An array of dataframes whose elements correspond to the 
 * data belonging to that bin based on the values in a given column. 
 * 
 * header: dataframe.h 
 */ 
// extern DATAFRAME **sort(DATAFRAME df, int column, double *binspace, 
// 	long num_bins) {

// 	/* 
// 	 * Bookkeeping 
// 	 * =========== 
// 	 * indeces: 	The index of the next row to fill in the sorted array 
// 	 * counts: 		The number of points belonging to each bin. 
// 	 * i, j, k: 	For-looping 
// 	 */ 
// 	int k; 
// 	long i, j; 
// 	long *indeces = long_zeroes(num_bins); 
// 	long *counts = hist(df, column, binspace, num_bins); 

// 	/* Allocate Memory */ 
// 	DATAFRAME **sorted = dataframe_array_initialize(num_bins); 
// 	for (i = 0l; i < num_bins; i++) {
// 		/* Copy the number of elements and dimensionality */ 
// 		sorted[i] = dataframe_initialize(); 
// 		sorted[i] -> num_rows = counts[i]; 
// 		sorted[i] -> num_cols = df.num_cols; 
// 		/* Allocate memory for a data table */ 
// 		sorted[i] -> data = (double **) malloc (counts[i] * sizeof(double *)); 
// 		for (j = 0l; j < counts[i]; j++) {
// 			sorted[i] -> data[j] = (double *) malloc (df.num_cols * 
// 				sizeof(double)); 
// 		} 
// 	} 
// 	/* Go through the data and assign each row in one foul swoop */ 
// 	for (i = 0l; i < df.num_rows; i++) { 
// 		/* Get the bin number corresponding to this row */ 
// 		long bin = get_bin_number(df.data[i][column], binspace, num_bins); 
// 		if (bin != -1l) { 
// 			/* 
// 			 * If it's within the binspace, copy this row, and increment the 
// 			 * row number of this bin by 1. 
// 			 */ 
// 			for (k = 0; k < df.num_cols; k++) { 
// 				sorted[bin] -> data[indeces[bin]][k] = df.data[i][k]; 
// 				indeces[bin]++; 
// 			}
// 		} else { 
// 			/* Outside the binspace, move on. */ 
// 			continue; 
// 		}
// 	} 

// 	free(indeces); 
// 	free(counts); 
// 	return sorted; 

// }

/* 
 * Determine the number of data points that fall within specified bin (i.e. 
 * a histogram) based on the values in a given column of the dataframe. 
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
 * 0 always. If it returns anything else, there was an internal error. 
 * 
 * header: dataframe.h 
 */ 
extern int hist(DATAFRAME df, int column, double *binspace, long num_bins, 
	long *counts) {

	/* 
	 * Get the bin number for each element and increment the counts array 
	 * up by one for each bin 
	 */ 
	long i; 
	for (i = 0l; i < df.num_rows; i++) {
		long bin = get_bin_number(df.data[i][column], binspace, num_bins); 
		if (bin != -1l) { 
			/* Increment that bin up by 1l */ 
			counts[bin]++; 
		} else {
			continue; /* Not in the binspace */ 
		} 
	} 
	return 0; 

}

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

/* 
 * Determine the indeces that would sort the dataframe from least to greatest 
 * according to the data in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column to sort based on 
 * 
 * Returns
 * ======= 
 * Type *long :: The indeces which sort the data from least to greatest. 
 */ 
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

/* 
 * Swap the i'th and j'th elements of a double pointer array 
 * 
 * Parameters 
 * ========== 
 * arr: 		The double pointer array itself 
 * i: 			The first index 
 * j: 			The second index 
 */ 
static void double_ptr_swap(double *arr, long i, long j) {

	double x = arr[i]; 
	double y = arr[j]; 
	arr[i] = y; 
	arr[j] = x; 

}


