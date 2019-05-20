/* 
 * Subroutines for the dataframe object 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h>
#include "dataframe.h" 
#include "utils.h" 

static long next_minimum_index(DATAFRAME df, int column, int *tracker); 

/* 
 * Determines the arithmetic mean of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the mean of 
 * 
 * Returns 
 * =======
 * Type double: The mean of the given column number 
 * 
 * header: dataframe.h 
 */ 
extern double column_mean(DATAFRAME df, int column) {

	long i; 
	double sum = 0; /* Start at zero */ 
	for (i = 0l; i < df.num_rows; i++) {
		sum += df.data[i][column]; /* Add each element */ 
	} 
	/* Return total of number of points */ 
	return sum / df.num_rows; 

} 

/* 
 * Determines the minimum of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the minimum of 
 * 
 * Returns 
 * ======= 
 * Type double: The minimum value 
 * 
 * header: dataframe.h 
 */ 
extern double column_min(DATAFRAME df, int column) {

	double minimum; 
	if (df.num_rows <= 0) { 
		return 0; /* Return zero if there isn't any data */ 
	} else if (df.num_rows == 1) { 
		return df.data[0][column]; /* There's only 1 data point */ 
	} else {
		long i; 
		/* Look at the first two and get the initial minimum */ 
		minimum = min(df.data[0][column], df.data[1][column]); 
		for (i = 2l; i < df.num_rows; i++) { 
			/* Look at each subsequent value and store the minimum */ 
			minimum = min(minimum, df.data[i][column]);  
		} 
		return minimum; 
	}

} 

/* 
 * Determines the maximum of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the maximum of 
 * 
 * Returns 
 * ======= 
 * Type double: The maximum value 
 * 
 * header: dataframe.h 
 */ 
extern double column_max(DATAFRAME df, int column) {

	double maximum; 
	if (df.num_rows <= 0) {
		return 0; /* Return zero if there isn't any data */ 
	} else if (df.num_rows == 1) {
		return df.data[0][column]; /* There's only 1 data point */ 
	} else {
		long i; 
		/* Look at the first two and get the initial maximum */ 
		maximum = max(df.data[0][column], df.data[1][column]); 
		for (i = 2l; i < df.num_rows; i++) {
			/* Look at each subsequent value and store the maximum */ 
			maximum = max(maximum, df.data[i][column]); 
		}
		return maximum; 
	}

} 






