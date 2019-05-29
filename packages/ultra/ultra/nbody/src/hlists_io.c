/* 
 * This is the source code for hlist file I/O 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "hlists.h" 
#include "utils.h" 

extern void write_header(FILE *in, FILE *out) {

	char (*line) = (char *) malloc (LINESIZE * sizeof(char)); 
	do { 
		fgets(line, LINESIZE, in); 
		fprintf(out, line); 
	} while (line != NULL && line[0] == '#'); 
	free(line); 

}

/* 
 * Reads in a line from a an ascii data file. 
 * 
 * Parameters 
 * ========== 
 * stream: 		The file object 
 * arr: 		A double pointer to put the line into 
 * dimension: 	The dimension of the file 
 * 
 * header: hlists.h 
 * 
 * Returns 
 * ======= 
 * Type int :: 1 if the end of the file has been found, 0 if there's more. 
 */ 
extern int read_line(FILE *stream, double *arr, const int dimension) {

	int i; 
	for (i = 0; i < dimension; i++) { 
		if (fscanf(stream, "%lf", &arr[i]) == EOF) {
			return 1; 
		} else {
			continue; 
		} 
	} 
	return 0; 

}


