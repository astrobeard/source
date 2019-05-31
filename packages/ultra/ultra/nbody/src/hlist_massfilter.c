/* 
 * This is the source code for the hlist mass filter 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <ctype.h> 
#include <math.h> 
#include "hlists.h" 
#include "utils.h" 

/* ---------- static routine comment headers not duplicated here ---------- */ 
static int header_length(char *file, char comment); 
static int file_dimension(char *file, int hlength); 

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
	int masscol) { 

	/* Debugging */ 
	comment = '#'; 

	/* 
	 * Bookkeeping 
	 * =========== 
	 * hlen: 			The length of the comment header in the file 
	 * dim: 			The dimensionality of the data file 
	 * 					(number of quantities on one line) 
	 * i: 				for-looping 
	 */ 
	int i, hlen = header_length(file, comment); 
	int dim = file_dimension(file, hlen);  
	if (hlen == -1) {
		/* header_length returns -1 on failure */ 
		return 1; 
	} else {} 

	/* Open the output file */ 
	FILE *out = fopen(outfile, "w"); 
	if (out == NULL) { 
		/* Return 2 on failure to write to the output file */ 
		fclose(out); 
		return 2; 
	}

	/* Open the input file */ 
	FILE *in = fopen(file, "r"); 
	if (in == NULL) { 
		/* Return 1 on failure to read the input file */ 
		fclose(in); 
		return 1; 
	} 

	/* Allocate memory for a dummy line of data */ 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	for (i = 0; i < hlen; i++) { 
		if (fgets(line, LINESIZE, in) == NULL) { 
			/* Returns 1 on failure to read the input file */ 
			fclose(in); 
			free(line); 
			return 1; 
		} else {
			continue; 
		} 
	} 
	free(line); /* free up the dummy line */ 

	double *data; 
	do { 
		/* 
		 * Go through the data file line by line and compare each mass 
		 * individually. This will save memory by not reading in every single 
		 * line. 
		 * 
		 * Start by allocating memory for one line of the data and read it in, 
		 * then free it up at the end of every loop. 
		 */ 
		data = (double *) malloc (dim * sizeof(double)); 
		for (i = 0; i < dim; i++) {
			if (fscanf(in, "%lf", &data[i])) {
				continue; 
			} else { 
				/* Reached the end of the data file, get out of this loop */ 
				free(data); 
				break; 
			} 
		} 

		/* Compare the log10 of the mass to the spcified minlogm */ 
		if (log10(data[masscol]) >= minlogm) {
			/* If it's above the resolution limit, write to the output file */ 
			for (i = 0; i < dim; i++) {
				fprintf(out, "%.5e\t", data[i]); 
			} 
			fprintf(out, "\n"); 
		} else {} 

		free(data); 
	} while (data != NULL); 

	/* Close the files and return 0 for success */ 
	fclose(in); 
	fclose(out); 
	return 0; 

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
 * The dimensionality of the data, assuming the file is square 
 */ 
static int file_dimension(char *file, int hlength) {

	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) return -1; 

	/* Read passed the header */ 
	int i; 
	int dim = 0; 
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
 * The number of lines in the header 
 */
static int header_length(char *file, char comment) {

	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) return -1; 

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
	 * comment charater. 
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



