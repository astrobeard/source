
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

#if 0 
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
	 * col: 		A copy of the column from the dataframe 
	 * rank: 		The rank indeces of each row number 
	 * new: 		The ordered data 
	 * i, j: 		For-looping 
	 * 
	 * Start by allocating memory for the rank indeces and calling 
	 * ptr_quickrank to determine the rank indeces of each row 
	 */ 
	int j; 
	double *col = dfcolumn(*df, column); 
	long i, *rank = ptr_rank(col, (*df).num_rows); 

	/* Allocate memory for the new data */ 
	double **new = (double **) malloc ((*df).num_rows * sizeof(double *)); 
	for (i = 0l; i < (*df).num_rows; i++) { 
		new[rank[i]] = (double *) malloc ((*df).num_cols * sizeof(double)); 
		for (j = 0; j < (*df).num_cols; j++) { 
			/* Pull the data from the next ranked row */ 
			new[rank[i]][j] = (*df).data[i][j]; 
		} 
	} 
	/* 
	 * Free up unnecessary memory as well as the old data. Point the dataframe 
	 * at the new data, return 0 for success, and call it a day. 
	 */ 
	free(col); 
	free(rank); 
	free(df -> data); 
	df -> data = new; 
	return 0; 

} 
#endif 

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

#if 0
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
#endif 

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

#if 0 
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
extern DATAFRAME **sort(DATAFRAME df, int column, double *binspace, 
	long num_bins) {

	/* 
	 * Bookkeeping 
	 * =========== 
	 * indeces: 	The index of the next row to fill in the sorted array 
	 * counts: 		The number of points belonging to each bin. 
	 * i, j, k: 	For-looping 
	 */ 
	int k; 
	long i, j; 
	long *indeces = long_zeroes(num_bins); 
	long *counts = (long *) malloc (num_bins * sizeof(long)); 
	hist(df, column, binspace, num_bins, counts); 

	/* Allocate Memory */ 
	DATAFRAME **sorted = dataframe_array_initialize(num_bins); 
	for (i = 0l; i < num_bins; i++) {
		/* Copy the number of elements and dimensionality */ 
		sorted[i] = dataframe_initialize(); 
		sorted[i] -> num_rows = counts[i]; 
		sorted[i] -> num_cols = df.num_cols; 
		/* Allocate memory for a data table */ 
		sorted[i] -> data = (double **) malloc (counts[i] * sizeof(double *)); 
		for (j = 0l; j < counts[i]; j++) {
			sorted[i] -> data[j] = (double *) malloc (df.num_cols * 
				sizeof(double)); 
		} 
	} 
	/* Go through the data and assign each row in one foul swoop */ 
	for (i = 0l; i < df.num_rows; i++) { 
		/* Get the bin number corresponding to this row */ 
		long bin = get_bin_number(df.data[i][column], binspace, num_bins); 
		if (bin != -1l) { 
			/* 
			 * If it's within the binspace, copy this row, and increment the 
			 * row number of this bin by 1. 
			 */ 
			for (k = 0; k < df.num_cols; k++) { 
				sorted[bin] -> data[indeces[bin]][k] = df.data[i][k]; 
				indeces[bin]++; 
			}
		} else { 
			/* Outside the binspace, move on. */ 
			continue; 
		}
	} 

	free(indeces); 
	free(counts); 
	return sorted; 

} 
#endif 

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

