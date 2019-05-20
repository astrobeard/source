
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here  ---------- */ 
static long *rank_indeces(DATAFRAME df, int column); 
static void ptr_swap(long *arr, long i, long j); 


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

static long *rank_indeces(DATAFRAME df, int column) {

	/* Run the operations on a copy of the indeces */ 
	long i, j, *indeces = range(0, df.num_rows); 

	for (i = 0l; i < df.num_rows; i++) {
		/* 
		 * Look the column'th element of each subsequent row and find the 
		 * smallest index. Then swap the indeces. 
		 */ 
		long smallest = i; 
		for (j = i + 1l; j < df.num_rows; j++) {
			if (df.data[j][column] <= df.data[smallest][column]) {
				smallest = j; 
			} else {
				continue; 
			}
		}
		ptr_swap(indeces, i, j); 
	} 
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
static void ptr_swap(long *arr, long i, long j) {

	long x = arr[i]; 
	long y = arr[j]; 
	arr[i] = y; 
	arr[j] = x; 

}


