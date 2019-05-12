
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */
static int get_bin_number(double value, double *binspace, int num_bins); 
static long *rank_indeces(DATAFRAME df, int column); 
static long next_minimum_index(DATAFRAME df, int column, int *tracker); 


/* 
 * Generates equal number samples from least to greatest based on the values 
 * within a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe to sort 
 * column: 			The column to sort based on 
 * num_bins: 		The number of bins to sort into 
 * 
 * Returns 
 * ======= 
 * Type: **DATAFRAME. An array of dataframes sorted into equal number bins from 
 * least to greatest based on a column number. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **equal_number_samples(DATAFRAME df, int column, 
	int num_bins) { 

	int i;

	/* Make sure that there are more points in the data than bins -> failure */ 
	if (df.num_rows < num_bins) {
		return NULL; 
	} else {} 

	/* Make use of the rank_by_column function */ 
	DATAFRAME *ordered = rank_by_column(df, column); 

	/* 
	 * The number of elements in each bin. This prescription loses a 
	 * few points at the maximum, but this function is intended to be 
	 * used with high N datasets anyway. 
	 */ 
	long j, n = (*ordered).num_rows / num_bins; /* integer division */ 
	DATAFRAME **binned = dataframe_array_initialize(num_bins); 
	for (i = 0; i < num_bins; i++) { 
		binned[i] = dataframe_initialize(); 
		binned[i] -> num_rows = n; 
		binned[i] -> num_cols = (*ordered).num_cols; 
		binned[i] -> data = (double **) malloc (n * sizeof(double *)); 
		for (j = 0l; j < n; j++) {
			/* Copy the next n elements into the data for this bin. */ 
			binned[i] -> data[j] = copy_double_ptr(
				(*ordered).data[i * num_bins + j], 
				(*ordered).num_cols 
			); 
		} 
	} 
	free_dataframe(ordered); 
	return binned; 

}

/* 
 * Sorts the data within a dataframe into a given binspace based on the 
 * values within a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe to sort 
 * column: 			The column to sort based on 
 * binspace: 		The binspace to sort the data into 
 * num_bins: 		The number of bins. This is the number of elements in the 
 * 					binspace array minus 1. 
 * 
 * Returns 
 * ======= 
 * Type: **DATAFRAME. The array of dataframes that hold the data points that 
 * lie in each bin. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **sort_by_bins(DATAFRAME df, int column, double *binspace, 
	int num_bins) {

	int i, j, *indeces = int_zeroes(num_bins); /* Bookkeeping */ 

	/* First figure out how many are in each bin */ 
	long k, *counts = histogram(df, column, binspace, num_bins); 

	/* 
	 * Allocate memory for an array of dataframes and fill each element 
	 * using the sieve_new_frame() and sieve_same_frame() functions 
	 * (dataframe_sieve.c). 
	 */ 
	DATAFRAME **sorted = dataframe_array_initialize(num_bins); 
	for (i = 0; i < num_bins; i++) {
		sorted[i] = sieve_new_frame(df, column, binspace[i], 4); 
		if (sieve_same_frame(sorted[i], column, binspace[i + 1], 2)) {
			/* 1 returned on failure, send back NULL in this case. */ 
			return NULL; 
		} else {}
	} 

	/* Free up memory and return */ 
	free(indeces); 
	free(counts); 
	return sorted;

}

/* 
 * Obtain counts within a specified binspace (i.e. histogram counts) based on 
 * the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe holding the data 
 * column: 			The column to sort by 
 * binspace: 		A pointer to the histogram bin edges 
 * num_bins: 		The number of bins. This is the number of elements in the 
 * 					binspace array minus 1. 
 * 
 * Returns 
 * ======= 
 * Type: *long. The counts within each bin. 
 * 
 * header: dataframe.h 
 */ 
extern long *histogram(DATAFRAME df, int column, double *binspace, 
	int num_bins) {

	int bin; 
	/* Start with an array of zeroes */ 
	long i, *hist = long_zeroes(num_bins); 
	for (i = 0l; i < df.num_rows; i++) { 
		/* Get the bin number for the given value */ 
		bin = get_bin_number(df.data[i][column], binspace, num_bins); 
		if (bin >= 0) { 
			hist[bin]++; 
		} else if (bin == -1) {
			continue; 
		} else { /* This shouldn't ever happen */ 
			printf("ERROR in histogram.\n"); 
			printf("Error code: dataframe_sorting.1\n"); 
			exit(0); 
		} 
	} 
	return hist; /* Return the counts */ 

}

/* 
 * Sorts the data within the dataframe based on a given column from least to 
 * greatest and returns a new dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column to sort based on 
 * 
 * Returns 
 * ======= 
 * A dataframe whose data are sorted. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *rank_by_column(DATAFRAME df, int column) {

	/* Get a new dataframe */ 
	DATAFRAME *new = dataframe_initialize(); 
	new -> num_rows = df.num_rows; 
	new -> num_cols = df.num_cols; 

	/* Get the proper order from the subroutine rank_indeces() */ 
	long i, *order = rank_indeces(df, column); 
	int j; 

	/* Allocate memory for the new data and copy it over */ 
	new -> data = (double **) malloc (df.num_rows * sizeof(double *)); 
	for (i = 0l; i < df.num_rows; i++) {
		new -> data[i] = (double *) malloc (df.num_cols * sizeof(double)); 
		for (j = 0; j < df.num_cols; j++) {
			new -> data[i] = copy_double_ptr(df.data[order[i]], df.num_cols); 
		} 
	} 

	free(order); 
	return new; 

} 

/* 
 * Determines the bin number of a given value within a specified binspace. 
 * 
 * Parameters 
 * ========== 
 * value: 		The value to get the bin number for 
 * binspace:	The binspace itself 
 * num_bins:	The length of the binspace array minus 1 (number of bins) 
 * 
 * Returns 
 * ======= 
 * Type int: the bin number itself. 
 */ 
static int get_bin_number(double value, double *binspace, int num_bins) {

	int i; 
	for (i = 0; i < num_bins; i++) { 
		/* Look at each adjacent pair of bins individually */ 
		if (binspace[i] <= value && value <= binspace[i + 1]) {
			return i; 
		} else {
			continue; 
		}
	}
	return -1; 

}

/* 
 * Determines the indeces of the data that would sort it least to greatest 
 * based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to sort by 
 */ 
static long *rank_indeces(DATAFRAME df, int column) {

	/* Keep track of the points already looked at */ 
	int *tracker = int_zeroes(df.num_rows); 
	/* Allocate memory for the actual ordered indeces */ 
	long i, *order = (long *) malloc (df.num_rows * sizeof(long)); 
	for (i = 0l; i < df.num_rows; i++) { 
		/* Get the next minimum that hasn't been recorded */ 
		order[i] = next_minimum_index(df, column, tracker); 
		if (order[i] == -1l) { 
			return NULL; /* -1l is the error value */ 
		} else { 
			tracker[order[i]] = 1; /* Flip the switch on the tracker */ 
		} 
	} 
	/* Free up the tracker's memory and return the order */ 
	free(tracker); 
	return order; 

}

/* 
 * Subroutine of rank_indeces() function. Determines the index of the next 
 * minimum value in the column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column that is being sorted by 
 * tracker: 	The boolean array describing whether or not each value has 
 * 				been recorded 
 * 
 * Returns 
 * ======= 
 * Type long: The index of the minimum value that. -1l if there is no minimum 
 * that hasn't yet been recorded. 
 */ 
static long next_minimum_index(DATAFRAME df, int column, int *tracker) {

	long i, first = -1l, second = -1l; 
	/* Find the first two non-tested value */ 
	for (i = 0l; i < df.num_rows; i++) {
		if (tracker[i]) {
			continue; /* Keep going if it's already been looked at */ 
		} else if (first == -1l) {
			first = i; /* Found the first one */ 
		} else if (second == -1l) {
			second = i; 
			break; /* Found them both, done */ 
		}
	}

	if (first == -1l) {
		/* If first == -1l, they've all been sorted */ 
		return -1l; 
	} else if (second == -1l) {
		/* If second == -1l, there's only one value left */ 
		return first; 
	} else {
		/* Otherwise proceed to increment through the rest of the data */ 
		double minimum = min(df.data[first][column], df.data[second][column]); 
		for (i = first; i < df.num_rows; i++) {
			if (df.data[i][column] <= minimum) {
				return i; 
			} else {
				continue; 
			}
		}
	} 

	/* 
	 * If the code somehow gets here (which it shouldn't), it didn't found a 
	 * minimum in the for-loop, which means the returned value should be -1l 
	 * anyway. 
	 */ 
	return -1l; 

}


