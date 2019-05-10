/*
 * In this script the file I/O for the snapshot object is written. 
 */ 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include "snapshot.h" 

/* ----------- static routine comment headers not duplicated here ----------- */ 
static int header_length(char *file, char comment); 
static int file_dimension(char *file, int hlength); 
static long num_lines(char *file); 

static long LINESIZE = 100000l; 

/* 
 * Reads in the data from a file and stores it in a snapshot object's data 
 * field. 
 * 
 * Parameters 
 * ========== 
 * file:		The name of the file as a character pointer 
 * 
 * header: snapshot.h 
 */
extern int populate_data_from_file(SNAPSHOT *snap, char *file, char comment) { 

	int hlen = header_length(file, comment);

	/* 
	 * Determine the number of data points and the dimensionality of the 
	 * data file from the static routines below. 
	 */ 
	snap -> num_rows = num_lines(file) - header_length(file, comment); 
	snap -> num_cols = file_dimension(file, hlen); 

	/* Error checking */ 
	if ((*snap).num_rows == 0 || (*snap).num_cols == -1) {
		return 1; 
	} else {} 

	/* Open the file and read past the header */  
	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) return 1;
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	long i; 
	int j; 
	for (j = 0; j < hlen; j++) {
		if (fgets(line, LINESIZE, in) == NULL) {
			return 1; 
		} else { 
			continue; 
		}
	}

	/* Allocate memory for the data */ 
	snap -> data = (double **) malloc ((*snap).num_rows * sizeof(double *)); 
	for (i = 0l; i < (*snap).num_rows; i++) {
		snap -> data[i] = (double *) malloc ((*snap).num_cols * sizeof(double)); 
		/* Read in each value at a time and store it within the snapshot */ 
		for (j = 0; j < (*snap).num_cols; j++) {
			if (fscanf(in, "%lf", &(snap -> data[i][j]))) {
				continue; 
			} else { 
				fclose(in); 
				free(line); 
				printf("ERROR reading file: %s\n", file); 
				printf("Error code: io.4"); 
				exit(0); 
			}
		}
	}

	/* Close the file, free up memory, and return a 0 for success */ 
	fclose(in); 
	free(line);
	return 0; 

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
 * Determines the number of lines in a file given its name as a character 
 * pointer. 
 * 
 * Parameters 
 * ========== 
 * file: 		The name of the file as a character pointer 
 * 
 * Returns 
 * ======= 
 * The number of lines 
 */ 
static long num_lines(char *file) {

	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) return -1; 

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
	/* Chose the files, free up the memory, and return */ 
	fclose(in); 
	free(line); 
	return n; 

}







