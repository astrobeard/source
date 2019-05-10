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

	long *indeces = range(0, (*snap).num_rows); 
	return indeces; 

}


