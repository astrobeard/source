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
			/* Copy the column'th element from each row and return the pointer */ 
			arr[i] = df.data[i][column]; 
		} 
		return arr; 
	}

} 

/* 
 * Determine the minimum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value from 
 * 
 * Returns 
 * ======= 
 * Type double :: The minimum value stored in that column of the data 
 * 0 if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double dfcolumn_min(DATAFRAME df, int column) {

	if (column < 0 || column >= df.num_cols) {
		/* If it's outside the allowed range of column numbers */ 
		return 0; 
	} else {
		/* Take the column and pass to ptr_min */ 
		return ptr_min(dfcolumn(df, column), df.num_rows); 
	}

} 

/* 
 * Determine the maximum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The maximum value stored in that column of the data 
 * 0 if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double dfcolumn_max(DATAFRAME df, int column) {

	if (column < 0 || column >= df.num_cols) {
		/* If it's outside the allowed range of column numbers */ 
		return 0; 
	} else {
		/* Take the column and pass to ptr_max */ 
		return ptr_max(dfcolumn(df, column), df.num_rows); 
	}

} 

/* 
 * Determine the sum of the values stored in a column of the dataframe 
 * 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The sum of the values in that column 
 * 0 if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double dfcolumn_sum(DATAFRAME df, int column) {

	if (column < 0 || column >= df.num_cols) {
		/* If it's outside the allowed range of column numbers */ 
		return 0; 
	} else {
		/* Take the column and pass to ptr_sum */ 
		return ptr_sum(dfcolumn(df, column), df.num_rows); 
	}

} 

/* 
 * Determine the arithmetic mean of the value stored in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The arithmetic mean of the data in that column 
 * 0 if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double dfcolumn_mean(DATAFRAME df, int column) {

	if (column < 0 || column >= df.num_cols) {
		/* If it's outside the allowed range of column numbers */ 
		return 0; 
	} else {
		/* Take the column and pass to ptr_mean */ 
		return ptr_mean(dfcolumn(df, column), df.num_rows); 
	}

}






