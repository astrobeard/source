/* 
 * Subroutines for the dataframe object 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h>
#include "dataframe.h" 
#include "utils.h" 

/* 
 * Takes a column from the data and returns a double pointer to it 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to take the column from 
 * column: 		The column number to take 
 * 
 * Returns 
 * ======= 
 * Type *double :: The column'th element of each row in the dataframe 
 * NULL if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double *dfcolumn(DATAFRAME df, int column) {

	if (column < 0 || column >= df.num_cols) {
		/* If it's outside the allowed range of column numbers */ 
		return NULL; 
	} else {
		long i; 
		/* Allocate the memory */ 
		double *arr = (double *) malloc (df.num_rows * sizeof(double)); 
		for (i = 0l; i < df.num_rows; i++) { 
			/* 
			 * Copy the column'th element from each row and return the pointer 
			 */ 
			arr[i] = df.data[i][column]; 
		} 
		return arr; 
	}

} 

/* 
 * Adds a new column to the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			A pointer to the dataframe to put the new column into 
 * arr: 		A pointer to the array to store as the new column 
 * 
 * Returns 
 * ======= 
 * 0 always; anything else is a SystemError 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_new(DATAFRAME *df, double *arr) {

	long i; 
	for (i = 0l; i < (*df).num_rows; i++) {
		df -> data[i] = (double *) realloc (df -> data[i], 
			((*df).num_cols + 1) * sizeof(double *)); 
		df -> data[i][(*df).num_cols] = arr[i]; 
	} 
	df -> num_cols++; 
	return 0; 

} 

/* 
 * Modify a column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			A pointer to the dataframe to be modified 
 * arr: 		A pointer to the array representing the new values in the given 
 * 				column 
 * column: 		The column number to modify 
 * 
 * Returns 
 * ======= 
 * 0 always; anything else is a SystemError 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_modify(DATAFRAME *df, double *arr, int column) {

	long i; 
	for (i = 0l; i < (*df).num_rows; i++) {
		df -> data[i][column] = arr[i]; 
	} 
	return 0; 

}

/* 
 * Determine the minimum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value from 
 * ptr: 		A pointer to put the minimum value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_min(DATAFRAME df, int column, double *ptr) {

	if (column < 0 || column >= df.num_cols) {
		return 1; /* return 1 on failure */ 
	} else { 
		double *col = dfcolumn(df, column); 
		*ptr = ptr_min(col, df.num_rows); 
		free(col); 
		return 0; 
	}

}

/* 
 * Determine the maximum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value from 
 * ptr: 		A pointer to put the maximum value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_max(DATAFRAME df, int column, double *ptr) {

	if (column < 0 || column >= df.num_cols) {
		return 1; /* return 1 on failure */ 
	} else { 
		double *col = dfcolumn(df, column); 
		*ptr = ptr_max(col, df.num_rows); 
		free(col); 
		return 0; 
	} 

} 

/* 
 * Determine the sum of the values stored in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * ptr: 		A pointer to put the sum in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_sum(DATAFRAME df, int column, double *ptr) {

	if (column < 0 || column >= df.num_cols) {
		return 1; /* return 1 on failure */ 
	} else { 
		double *col = dfcolumn(df, column); 
		*ptr = ptr_sum(col, df.num_rows); 
		free(col); 
		return 0; 
	}

}

/* 
 * Determine the arithmetic mean of the value stored ina column of the 
 * dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to find the mean value of 
 * ptr: 		A pointer to put the mean value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_mean(DATAFRAME df, int column, double *ptr) { 

	if (column < 0 || column >= df.num_cols) { 
		return 1; /* return 1 on failure */ 
	} else { 
		double *col = dfcolumn(df, column); 
		*ptr = ptr_mean(col, df.num_rows); 
		free(col); 
		return 0; 
	} 

} 

/* 
 * Determine the median of a given column of the data 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the median of 
 * ptr: 		A pointer to put the median value into 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_median(DATAFRAME df, int column, double *ptr) {

	if (column < 0 || column >= df.num_cols) {
		return 1; /* return 1 on failure */ 
	} else {
		/* Sort that row from least to greatest */ 
		double *col = dfcolumn(df, column); 
		double *sorted_column = ptr_sort(col, df.num_rows); 
		if (df.num_rows % 2 == 0) { 
			/* 
			 * If there's an even number of data points, the median is the 
			 * arithmetic mean of the middle two data points 
			 */ 
			*ptr = (sorted_column[df.num_rows / 2l] + 
				sorted_column[df.num_rows / 2l - 1l]) / 2; 
		} else {
			/* If there's an odd number, the median is the middle value */ 
			*ptr = sorted_column[(df.num_rows - 1l) / 2l]; 
		} 
		free(col); 
		free(sorted_column); 
		return 0; 
	}

}

/* 
 * Determine the standard deviation of a column of the data. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column:	 	The column number to find the standard deviation of 
 * ptr: 		A pointer to put the standard deviation into 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int dfcolumn_std(DATAFRAME df, int column, double *ptr) {

	if (column < 0 || column >= df.num_cols) {
		return 1; /* return 1 on failure */ 
	} else { 
		/* Find the squared difference between each data point and the mean */ 
		long i; 
		double *col = dfcolumn(df, column); 
		double *diff = (double *) malloc (df.num_rows * sizeof(double)); 
		double mean = ptr_mean(col, df.num_rows); 
		for (i = 0l; i < df.num_rows; i++) {
			diff[i] = pow(df.data[i][column] - mean, 2); 
		} 
		/* 
		 * Recast the mean as the mean squared difference, take the sqrt, and 
		 * return. Free up the memory, then return 0 for success. 
		 */ 
		mean = ptr_mean(diff, df.num_rows); 
		free(diff); 
		free(col); 
		*ptr = sqrt(mean); 
		return 0; 
	}

} 






