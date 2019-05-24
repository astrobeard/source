/* 
 * This file scripts the source code for the dataframe sieve function. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
// static double **copy_only_filtered(DATAFRAME df, int *test); 
static int *get_test_results(DATAFRAME df, int column, double value, 
	int relational_code); 

/* 
 * Filter the dataset based on some condition applied to the values stored in 
 * a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 					A pointer to the dataframe to modify 
 * column: 				The column number to filter based on 
 * value: 				The value to compare to for filtering 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 						6 for != 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */ 
extern int sieve(DATAFRAME *df, int column, double value, int relational_code) {

	/* 
	 * Bookeeping 
	 * ========== 
	 * test: 		0s at the positions of data points that don't pass the test, 
	 * 				1s at the ones that do 
	 * new: 		The new data 
	 * i, j: 		for-looping 
	 * n: 			The line number of the next row of new to fill 
	 * 
	 * Start by figuring out which lines pass the test 
	 */ 
	long i, n = 0l; 
	int j, *test = get_test_results(*df, column, value, relational_code); 
	if (test == NULL) return 1; /* return 1 on failure */ 

	/* Allocate memory for the number of lines that pass */ 
	double **new = (double **) malloc (int_sum(test, (*df).num_rows) * 
		sizeof(double *)); 
	for (i = 0l; i < (*df).num_rows; i++) { 
		if (test[i]) {
			/* 
			 * If this line passed the test, allocate memory for it and copy 
			 * each quantity over. 
			 */ 
			new[n] = (double *) malloc ((*df).num_cols * sizeof(double)); 
			for (j = 0; j < (*df).num_cols; j++) {
				new[n][j] = (*df).data[i][j]; 
			} 
			n++; /* Next line */ 
		} else { 
			continue; 
		} 
	} 
	/* A new number of rows */ 
	df -> num_rows = int_sum(test, (*df).num_rows); 
	free(test); 
	free(df -> data); 
	df -> data = new; 
	return 0; /* return 0 on success */ 

}

/* 
 * Iterates over each row of the dataframe and determines if each row satisfies 
 * a given relation. 
 * 
 * Parameters 
 * ========== 
 * df: 					The DATAFRAME struct 
 * column:				The column to condition the data on 
 * value: 				The value to compare each column to 
 * relational_code: 	1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 						6 for != 
 * 
 * Returns 
 * ======= 
 * An array of 0s and 1. 0s at the position of rows that failed the test and 
 * 1 at the position of those that passed. 
 */ 
static int *get_test_results(DATAFRAME df, int column, double value, 
	int relational_code) {

	/* 
	 * Allocate memory for an array of boolean ints, and determine if each 
	 * row satisfies the relation.  
	 */ 
	long i; 
	int *test = (int *) malloc (df.num_rows * sizeof(int)); 
	for (i = 0l; i < df.num_rows; i++) {
		/* Look at each value and store a 1 if the relation holds, else 0. */ 
		if (relational_code == 1) { 
			test[i] = df.data[i][column] < value; /* 1: < */ 
		} else if (relational_code == 2) { 
			test[i] = df.data[i][column] <= value; /* 2 <= */  
		} else if (relational_code == 3) { 
			test[i] = df.data[i][column] == value; /* 3: == */ 
		} else if (relational_code == 4) {
			test[i] = df.data[i][column] >= value; /* 4: >= */ 
		} else if (relational_code == 5) {
			test[i] = df.data[i][column] > value; /* 5: > */ 
		} else if (relational_code == 6) {
			test[i] = df.data[i][column] != value; /* 6: != */ 
		} else { 
			free(test); 
			return NULL; /* Unallowed relational code */ 
		}
	} 
	return test; 

} 

#if 0
/* 
 * Returns a double pointer to a data table that contains only the rows of the 
 * a dataframed that passed a filter test. 
 * 
 * Parameters 
 * ========== 
 * df:			The DATAFRAME struct itself 
 * test: 		The array produced by the get_test_results() function. 
 * 
 * Returns 
 * ======= 
 * A double pointer containing only the rows that have a 1 at the same index 
 * in the test array. This double pointer can then be saved into a new 
 * dataframe struct. 
 */ 
static double **copy_only_filtered(DATAFRAME df, int *test) {

	/* 
	 * Since test is an array of zeroes and ones, the number of elements in 
	 * the filtered array is simply the sum of the test array. Allocate memory  
	 * for the data, and copy each value.  
	 */ 	
	double **new = (double **) malloc (int_sum(test, df.num_rows) * 
		sizeof(double *)); 

	int j; 
	long i, n = 0l; 
	for (i = 0l; i < df.num_rows; i++) {
		/* Look at each element and see if it passed the test */ 
		if (test[i]) {
			new[n] = (double *) malloc (df.num_cols * sizeof(double)); 
			for (j = 0; j < df.num_cols; j++) {
				new[n][j] = df.data[i][j]; 
			}
			n++; /* next element of the new array */ 
		} else {
			/* If not, keep going */ 
			continue; 
		}
	} 

	return new; 

} 
#endif 

