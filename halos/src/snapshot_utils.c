
#include <stdlib.h> 
#include "snapshot.h" 

/* 
 * Frees up the memory stored within a SNAPSHOT 
 * 
 * Parameters 
 * ========== 
 * snap: 		The SNAPSHOT struct itself 
 * 
 * header: snapshot.h 
 */ 
extern void free_snapshot(SNAPSHOT *snap) {

	free(snap -> data); 

}

/* 
 * Emulates python's range function 
 * 
 * Parameters 
 * ========== 
 * start:		The starting value of the resultant array 
 * stop: 		The stopping value of the resultant array 
 * 
 * Returns 
 * ======= 
 * An array of longs containing every value between start and 
 * stop - 1l (inclusive). 
 */ 
extern long *range(long start, long stop) {

	/* Allocate memory */ 
	long *arr = (long *) malloc ((stop - start) * sizeof(long)); 
	long i; 
	/* Store every value between start and stop - 1l (inclusive) */
	for (i = start; i < stop; i++) {
		arr[i] = i; 
	}
	/* Return the resulting array */ 
	return arr; 

}

extern long *zeroes(long length) {

	long i, *arr = (long *) malloc (length * sizeof(length)); 
	for (i = 0l; i < length; i++) {
		arr[i] = 0l; 
	}
	return arr; 
	
}


