/* 
 * This is the header file for hlist C-routines 
 */ 

#ifndef HLISTS_H 
#define HLISTS_H 

#include <stdio.h> /* FILE struct */  

/* 
 * Condenses an hlist file based on a minimum halo mass 
 * 
 * Parameters 
 * ========== 
 * file: 			The name of the hlist ascii text file to condense 
 * commenter: 		The commenting character in the header 
 * 					This is passed as a pointer, but the commenting character 
 * 					will be taken as the first element 
 * outfile: 		The name of the output ascii text file 
 * minlogm: 		The log10 of the minimum halo mass 
 * masscol: 		The column number of halo virial masses 
 * 
 * Returns 
 * ======= 
 * 0 on sucess, 1 on failure to read data, 2 on failure to write data 
 * 
 * source: hlists_massfilter.c 
 */ 
extern int condense(char *file, char *commenter, char *outfile, double minlogm, 
	int masscol); 







/* ------------------------------- FILE I/O ------------------------------- */ 

/* 
 * Determines the length of a header given the name of the file and a 
 * commenting character 
 * 
 * Parameters 
 * ========== 
 * file:		The name of the file as a character pointer 
 * comment: 	The commenting character 
 * 
 * Returns 
 * ======= 
 * The number of lines in the header; -1 on failure to read the file. 
 * 
 * source: hlists_io.c 
 */
extern int header_length(char *file, char comment); 

/* 
 * Determines the dimensionality of the file given the length of the header 
 * and the name of the file as a character pointer. 
 * 
 * Parameters 
 * ========== 
 * file:		The name of the file as a character pointer 
 * hlength:		The length of the header 
 * 
 * Returns 
 * ======= 
 * The dimensionality of the data, assuming the file is square; -1 on failure 
 * to read from the input file 
 * 
 * source: hlists_io.c 
 */ 
extern int file_dimension(char *file, int hlength); 

/*
 * Determines the number of lines in a file given its name as a character 
 * pointer. 
 * 
 * Parameters 
 * ========== 
 * file: 		The name of the file as a character pointer 
 * 
 * Returns 
 * ======= 
 * The number of lines; -1l on failure to read the input file 
 * 
 * header: hlists.h 
 */ 
extern long num_lines(char *file); 


#endif /* HLISTS_H */ 

