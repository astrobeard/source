/* 
 * In this script the file I/O for hlists is written. 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <ctype.h> 
#include <math.h> 
#include "hlists.h" 
#include "utils.h" 

/* ---------- static routine comment headers not duplicated here ---------- */ 

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
 * header: hlists.h  
 */
extern int header_length(char *file, char comment) {
	
	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) {
		fclose(in); 
		return -1; 
	} else {} 

	int n = 0; 
	/* Store a line in memory */ 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	if (fgets(line, LINESIZE, in) == NULL) {
		fclose(in); 
		free(line); 
		printf("ERROR reading file: %s\n", file); 
		printf("Error code: io.1\n"); 
		exit(0); 
	} else {} 

	/* 
	 * Add up all of the lines at the beginning that start with the specified 
	 * comment character. 
	 */ 
	while (line[0] == comment) {
		n++; 
		if (fgets(line, LINESIZE, in) == NULL) {
			fclose(in); 
			free(line); 
			printf("ERROR reading file: %s\n", file); 
			printf("Error code: io.2\n"); 
			exit(0); 
		} else {
			continue; 
		} 
	} 

	/* Close the file and return */ 
	fclose(in); 
	free(line); 
	return n; 

}

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
 * header: hlists.h 
 */ 
extern int file_dimension(char *file, int hlength) {

	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) {
		fclose(in); 
		return -1; 
	} else {} 

	/* Read passed the header */ 
	int i, dim = 0; 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	for (i = 0; i <= hlength; i++) {
		if (fgets(line, LINESIZE, in) == NULL) {
			fclose(in); 
			free(line); 
			printf("ERROR reading file: %s\n", file); 
			printf("Error code: io.3\n"); 
			exit(0); 
		} else {
			continue; 
		} 
	} 

	/*
	 * For any character in the line that is not whitespace, increment the 
	 * dimensionality up by one if the following character IS whitespace. 
	 */ 
	unsigned int j; 
	for (j = 0; j < strlen(line) - 1; j++) {
		if (isspace(line[j + 1]) && !isspace(line[j])) {
			dim++; 
		} else {
			continue; 
		} 
	} 

	/* Close the file and return */ 
	fclose(in); 
	free(line); 
	return dim; 

} 

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
extern long num_lines(char *file) {

	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) {
		fclose(in); 
		return -1l; 
	} else {} 

	/* 
	 * Store a line in memory and start reading the file. Don't stop reading 
	 * in new lines until there aren't any more lines to read in. Simply count 
	 * them along the way. 
	 */ 
	long n = 0l; 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	while (fgets(line, LINESIZE, in) != NULL) {
		n++; 
	} 

	/* Close files, free up memory, and return */ 
	fclose(in); 
	free(line); 
	return n; 

} 

