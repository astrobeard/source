/* 
 * Subroutines for the snapshot object 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h>
#include "snapshot.h" 

/* 
 * Sorts the data into a certain number of equal number subsamples based on 
 * the values in a given column 
 */ 
extern void generate_ordered_subsamples(SNAPSHOT *snap, int num_samples, 
	int col_num) {

}

static long *sort_indeces(SNAPSHOT *snap) {

	long *tracker = zeroes((*snap).num_rows); 
	long *indeces = range(0, (*snap).num_rows); 
	long *arr = (long *) malloc ((*snap).num_rows * sizeof(long)); 
	long i, j; 

	for (i = 0l; i < (*snap).num_rows; i++) {

	}

	return indeces; 

}

static long argmin(SNAPSHOT *snap, int col_num, long *tracker) {

	double minimum = min(
		(*snap).data[0][col_num], 
		(*snap).data[1][col_num]
	);

	long index; 
	if ((*snap).data[0][col_num] < (*snap).data[1][col_num]) {
		index = 0l; 
	} else {
		index = 1l;
	}

	long i; 
	for (i = 2l; i < (*snap).num_rows; i++) {
		if ((*snap).data[i][col_num] < minimum && !tracker[i]) {
			minimum = (*snap).data[i][col_num]; 
			index = i; 
		} else {
			continue; 
		}
	}

	return index; 

}


