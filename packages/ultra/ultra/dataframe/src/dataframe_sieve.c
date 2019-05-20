/* 
 * This file scripts the source code for the dataframe sieve function. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "dataframe.h" 
#include "utils.h" 

static double **copy_only_filtered(DATAFRAME df, int *test); 
static int *get_test_results(DATAFRAME df, int column, int value, 
	int relational_code); 

/* 
 * Filters the data based on a given condition on a given column and returns 
 * a new dataframe object. 
 * 
 * Parameters 
 * ========== 
 * df: 					The dataframe holding the data to filter 
 * column: 				The column to impose the filter on 
 * value: 				The value to test on 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 
 * Returns 
 * ======= 
 * A new dataframe whose data attribute contains only the rows which satisfy 
 * the condition df[row][column] ?(relational_code) value. 
 * 
 * NULL if the relational_code is not recognized. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *sieve_new_frame(DATAFRAME df, int column, int value, 
	int relational_code) {

	int *test = get_test_results(df, column, value, relational_code); 
	if (test == NULL) return NULL; 
	DATAFRAME *new = dataframe_initialize(); 
	new -> num_cols = df.num_cols;
	new -> num_rows = int_sum(test, df.num_rows); 
	new -> data = copy_only_filtered(df, test); 
	free(test); 
	return new; 

} 

/* 
 * Filters the data based on a given condition and removes all other data 
 * from the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 					The dataframe holding the data to filter 
 * column: 				The column to impose the filter on 
 * value: 				The value to test on 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 
 * Returns 
 * ======= 
 * an int: 0 if successful, 1 if failure. 
 * 
 * header: dataframe.h 
 */ 
extern int sieve_same_frame(DATAFRAME *df, int column, int value, 
	int relational_code) {

	int *test = get_test_results(*df, column, value, relational_code); 
	if (test == NULL) return 1; 
	double **new = copy_only_filtered(*df, test); 
	free(df -> data); 
	df -> data = new; 
	return 0; 

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
 * 
 * Returns 
 * ======= 
 * An array of 0s and 1. 0s at the position of rows that failed the test and 
 * 1 at the position of those that passed. 
 */ 
static int *get_test_results(DATAFRAME df, int column, int value, 
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
			test[i] = value < df.data[i][column]; /* 1: < */ 
		} else if (relational_code == 2) {
			test[i] = value <= df.data[i][column]; /* 2: <= */ 
		} else if (relational_code == 3) {
			test[i] = value == df.data[i][column]; /* 3: == */ 
		} else if (relational_code == 4) {
			test[i] = value >= df.data[i][column]; /* 4: >= */ 
		} else if (relational_code == 5) {
			test[i] = value > df.data[i][column]; /* 5: > */ 
		} else { 
			free(test); 
			return NULL; /* Unallowed relational code */ 
		}
	} 
	return test; 

} 

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

