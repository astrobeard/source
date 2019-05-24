/*
 * In this script the file I/O for the dataframe object is written. 
 */ 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include "dataframe.h" 
#include "utils.h" 

/* ---------- static routine comment headers not duplicated here ---------- */ 
static int header_length(char *file, char comment); 
static int file_dimension(char *file, int hlength); 
static long num_lines(char *file); 

/* 
 * Reads in the data from a file and stored it in a dataframe object's data 
 * field. Takes user-specified columns from the file. 
 * 
 * Parameters 
 * ========== 
 * df: 			A pointer to the dataframe itself 
 * file: 		The name of the file 
 * comment: 	The commenting character 
 * columns: 	The column numbers to take 
 * num_cols: 	The number of columns being imported 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: dataframe.h 
 */
extern int populate_from_file(DATAFRAME *df, char *file, char comment, 
	int *columns, int num_cols) {

	/* 
	 * debugging 
	 * ========= 
	 * For some reason this character can't get passed from python properly. 
	 * This needs to be sorted out before the comment character option can 
	 * be utilized. 
	 */ 
	comment = '#'; 

	/* 
	 * Bookkeeping 
	 * =========== 
	 * hlen: 		The length of the header in the file 
	 * dim: 		The dimensionality of the file 
	 * i, j: 		For-looping 
	 */ 
	long i; 
	int j, hlen = header_length(file, comment); 
	int dim = file_dimension(file, hlen); 
	df -> num_rows = num_lines(file) - hlen; 
	df -> num_cols = num_cols; 

	/* Error checking */ 
	if ((*df).num_rows == 0 || (*df).num_cols == -1) {
		return 1; 
	} else {} 

	/* Open the file and read past the header */ 
	FILE *in; 
	in = fopen(file, "r"); 
	if (in == NULL) return 1; 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	for (j = 0; j < hlen; j++) {
		if (fgets(line, LINESIZE, in) == NULL) {
			return 1; 
		} else {
			continue; 
		} 
	} 
	free(line); 

	/* Allocate memory for the data */ 
	df -> data = (double **) malloc ((*df).num_rows * sizeof(double *)); 
	for (i = 0l; i < (*df).num_rows; i++) { 
		/* Read in the next line */ 
		double *line = (double *) malloc (dim * sizeof(double)); 
		for (j = 0; j < dim; j++) {
			if (fscanf(in, "%lf", &line[j])) {
				continue; 
			} else {
				printf("ERROR reading file: %s\n", file); 
				printf("Error code: io.5\n"); 
				exit(0); 
			} 
		} 

		/* Allocate memory for the next row of the data and copy it over */ 
		df -> data[i] = (double *) malloc ((*df).num_cols * sizeof(double)); 
		for (j = 0; j < (*df).num_cols; j++) { 
			df -> data[i][j] = line[columns[j]]; 
		} 
		free(line); /* Free the temporary copy */ 
	} 
	fclose(in); 
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







