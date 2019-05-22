/* 
 * This is the header file for hlist C-routines 
 */ 

#ifndef HLISTS_H 
#define HLISTS_H 

#include <stdio.h> /* FILE struct */ 

/* 
 * Reads in a line from a an ascii data file. 
 * 
 * Parameters 
 * ========== 
 * stream: 		The file object 
 * arr: 		A double pointer to put the line into 
 * dimension: 	The dimension of the file 
 * 
 * Returns 
 * ======= 
 * Type int :: 1 if the end of the file has been found, 0 if there's more. 
 * 
 * header: hlists.h 
 */ 
extern int read_line(FILE *stream, double *arr, const int dimension); 


#endif /* HLISTS_H */ 

