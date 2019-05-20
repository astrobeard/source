
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static long *rank_indeces(DATAFRAME df, int column); 
static long next_minimum_index(DATAFRAME df, int column, int *tracker); 


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
// extern DATAFRAME *dfcolumn_order(DATAFRAME df, int column) {

// 	DATAFRAME *new = 

// } 

/* 
 * Determines the order of row numbers that would sort the dataframe from 
 * least to greatest based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to sort based on 
 * 
 * Returns 
 * ======= 
 * Type long :: The row numbers that would sort the dataframe 
 */ 
static long *rank_indeces(DATAFRAME df, int column) {

	long i; 
	int *tracker = int_zeroes(df.num_rows); 
	long *sorted = (long *) malloc (df.num_rows * sizeof(long)); 
	for (i = 0l; i < df.num_rows; i++) { 
		printf("\r%ld of %ld", i, df.num_rows); 
		long index = next_minimum_index(df, column, tracker); 
		tracker[index] = 1; 
		sorted[i] = index; 
	} 
	free(tracker); 
	return sorted; 

}

/* 
 * Subroutine of *rank_indeces(). Determines the index of the next minimum 
 * value in a given column when a portion of the data have already been 
 * considered. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number that we're sorting based on 
 * tracker: 	An array of boolean ints (0: hasn't been taken; 1: it has) 
 * 
 * Returns 
 * ======= 
 * Type long :: The index of the next minimum value in that column. 
 * -1l if all of the data have been looked at. 
 */ 
static long next_minimum_index(DATAFRAME df, int column, int *tracker) {

	/* 
	 * First find the first two values whose rank index hasn't yet been 
	 * found. Let first be a boolean int to describe whether or not we've 
	 * found the first one. 
	 */ 
	long i, start = -1l, first_index; 
	int first = 0; 
	for (i = 0l; i < df.num_rows; i++) {
		/* Start looking through the data */ 
		if (tracker[i]) {
			/* If this row has already been considered, move on */ 
			continue; 
		} else if (first) {
			/* 
			 * We've found the first one already. This is the second one. 
			 * Make note of the starting place and get out of the for loop 
			 */  
			start = i; 
			break; 
		} else {
			/* 
			 * This row hasn't been taken and it's the first minimum. 
			 * Bookkeep its location and flip the switch. 
			 */ 
			first_index = i; 
			first = 1; 
		}
	} 

	if (first && start == -1l) {
		/* 
		 * If this is the case, the code found the first minimum, but not the 
		 * second. This means there is only one value that hasn't been taken. 
		 * return it's index. 
		 */ 
		return first_index; 
	} else if (first) {
		/* 
		 * Having already checked if there isn't a second value to take, this 
		 * means that the previous for loop found two values that hadn't been 
		 * considered yet. Look through the rest of the data. 
		 */ 
		
		long index; 
		double minimum; 

		/* Figure out which one is the minimum and take it's index */ 
		if (df.data[first_index][column] <= df.data[start][column]) {
			minimum = df.data[first_index][column]; 
			index = first_index; 
		} else {
			minimum = df.data[start][column]; 
			index = start; 
		}

		/* Look at the rest of the data */ 
		for (i = start + 1l; i < df.num_rows; i++) {
			if (tracker[i]) { 
				/* If this row has already been looked at */ 
				continue; 
			} else if (df.data[i][column] <= minimum) { 
				/* If this one is lower, take it as the new minimum */ 
				minimum = df.data[i][column]; 
				index = i; 
			} else {
				/* 
				 * It's above the current minimum, which means it should've 
				 * been looked at anyway, so tracker[i] should = 1. 
				 */ 
				continue; 
			}
		}

		return index; 

	} else {
		/* 
		 * If the code gets here, it never found the first value that hadn't 
		 * been looked at. This means all of the data should've been looked 
		 * through. Return -1l in this case. 
		 */ 
		return -1l; 
	}

}


