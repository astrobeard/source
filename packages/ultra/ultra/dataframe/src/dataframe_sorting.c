
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static long get_bin_number(double value, double *binspace, long num_bins); 
static long *rank_indeces(DATAFRAME df, int column); 
static void long_ptr_swap(long *a, long *b); 
static void double_ptr_swap(double *a, double *b); 

/* 
 * Sorts a dataframe pointer in ascending order based on the data in a given 
 * column. 
 * 
 * Parameters 
 * ========== 
 * df: 			A pointer to the dataframe to sort 
 * column: 		The column number to sort based on 
 * 
 * Returns 
 * ======= 
 * 0 on success, anything else would be a system error. 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_order(DATAFRAME *df, int column) {

	/* 
	 * Bookkeeping 
	 * =========== 
	 * order: 		The rank index of each row of the dataframe 
	 * new: 		The new, sorted data 
	 * i, j: 		for-looping 
	 */ 
	int j; 
	long i, *order = rank_indeces(*df, column); 
	/* Allocate memory for the same number of rows */ 
	double **new = (double **) malloc ((*df).num_rows * sizeof(double *)); 
	for (i = 0l; i < (*df).num_rows; i++) { 
		/* Allocate memory for the next row */ 
		new[i] = (double *) malloc ((*df).num_cols * sizeof(double)); 
		for (j = 0; j < (*df).num_cols; j++) { 
			/* Pull the data from the next ranked row */ 
			new[i][j] = (*df).data[order[i]][j]; 
		} 
	} 
	/*
	 * Free up memory, reinitialize the data pointer, and return 0 for 
	 * success. 
	 */ 
	free(order); 
	free(df -> data); 
	df -> data = new; 
	return 0; 

} 

/* 
 * Take the data from a source dataframe and put into a destination dataframe 
 * only the data which lie in a given bin based on the values in a given 
 * column. 
 * 
 * Parameters 
 * ========== 
 * source: 			The source dataframe 
 * dest: 			The destination dataframe 
 * column: 			The column number that binning is based on 
 * bin: 			The left and right bin edges 
 * 
 * Returns 
 * ======= 
 * 0 always, anything else would be a system error 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_bin(DATAFRAME source, DATAFRAME *dest, int column, 
	double *bin) {

	/* The number of points that lie in this bin */ 
	int j;  
	long i, n = 0l, *counts = (long *) malloc (sizeof(long)); 
	*counts = 0l; 
	hist(source, column, bin, 1l, counts); 
	dest -> num_rows = *counts; 
	dest -> num_cols = source.num_cols; 

	dest -> data = (double **) malloc (*counts * sizeof(double *)); 
	for (i = 0l; i < source.num_rows; i++) { 
		if (!get_bin_number(source.data[i][column], bin, 1l)) {
			dest -> data[n] = (double *) malloc (source.num_cols * 
				sizeof(double)); 
			for (j = 0; j < source.num_cols; j++) {
				dest -> data[n][j] = source.data[i][j]; 
			} 
			n++; 
		} else { 
			continue; 
		} 
	} 
	free(counts); 
	return 0; 

} 

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
 * counts: 		A long pointer to put the number of counts into . This must 
 * 				have num_bins elements to the array 
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
 * Generates an equal number subsample off of a dataframe that has already been 
 * sorted into ascending order based on the data in a given column. 
 * 
 * Parameters 
 * ========== 
 * ordered: 		The ordered dataframe 
 * dest: 			The destination dataframe 
 * num_subs: 		The number of subsamples being generated 
 * index: 			The index of the subsample that is being generated 
 * 
 * Returns 
 * ======= 
 * 0 always; anything else is a SystemError 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_equal_number_subsample(DATAFRAME ordered, DATAFRAME *dest, 
	int num_subs, int index) {

	long i; 
	int j; 

	dest -> num_cols = ordered.num_cols; 
	dest -> num_rows = ordered.num_rows / num_subs; 
	dest -> data = (double **) malloc ((*dest).num_rows * sizeof(double *)); 

	for (i = 0; i < (*dest).num_rows; i++) {
		dest -> data[i] = (double *) malloc ((*dest).num_cols * sizeof(double)); 
		long row_num = ordered.num_rows / num_subs * index + i; 
		for (j = 0; j < (*dest).num_cols; j++) {
			dest -> data[i][j] = ordered.data[row_num][j]; 
		} 
	} 
	return 0; 

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
		double_ptr_swap(&col[i], &col[smallest]); 
		long_ptr_swap(&indeces[i], &indeces[smallest]); 
		/* printf("\r%ld of %ld", i, df.num_rows); */ 
	} 
	/* printf("\n"); */ 
	return indeces; 

} 

static void long_ptr_swap(long *a, long *b) {

	long x = *a; 
	*a = *b; 
	*b = x; 

} 

static void double_ptr_swap(double *a, double *b) {

	double x = *a; 
	*a = *b; 
	*b = x; 

}

