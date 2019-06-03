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
 * comment: 		The commenting character in the header 
 * outfile: 		The name of the output ascii text file 
 * minlogm: 		The log10 of the minimum halo mass 
 * masscol: 		The column number of halo virial masses 
 * 
 * Returns 
 * ======= 
 * 0 on sucess, 1 on failure to read data, 2 on failure to write data 
 * 
 * header: hlists.h 
 */ 
extern int condense(char *file, char comment, char *outfile, double minlogm, 
	int masscol); 


#endif /* HLISTS_H */ 

