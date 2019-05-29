/* 
 * Condense an hlist into only the lines above a given resolution limit. 
 * Reproduces the header of the file and takes all lines above a given 
 * logarithmic halo mass. 
 * 
 * ARGV 
 * ==== 
 * 1) 		Type str :: The name of the input file 
 * 2) 		Type str :: The name of the output file 
 * 3) 		Type double :: The minimum logarithmic halo mass in h^-1 Msun 
 * 4) 		Type int :: The column number (zero-index) of the halo mass 
 * 5) 		Type int :: The number of commented lines in the header 
 * 6) 		Type int :: The dimensionality of the hlist 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "hlists.h" 
#include "utils.h" 

/* ---------- Static routine comment headers not duplicated here ---------- */ 
static void set_globals(int argc, char **argv); 


/* --------------------------- Global Variables --------------------------- */ 
/* 
 * _INPUT_FILE_ :: The input file stream object 
 * _OUTPUT_FILE_ :: The output file stream object 
 * _MIN_LOG_MASS :: The minimum halo mass in log h^-1 Msun units 
 * _MASS_COLUMN_ :: The column number (zero-based) of the halo masses 
 * _HEADER_LENGTH_ :: The number of commented lines in the header 
 */ 
static FILE *_INPUT_FILE_, *_OUTPUT_FILE_; 
static double _MIN_LOG_MASS_; 
static int _MASS_COLUMN_, _HEADER_LENGTH_, _DIMENSION_; 

int main(int argc, char **argv) {

	int i; 

	/* Set the globals variables */ 
	set_globals(argc, argv); 

	/* 
	 * Write the header. Allocate memory for a string at the maximum linesize 
	 * (defined in utils.h) and read each line. Write it to the output file 
	 * immediately. 
	 */ 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	for (i = 0; i < _HEADER_LENGTH_; i++) {
		if (fgets(line, LINESIZE, in) == NULL) {
			printf("Error reading file: %s\n", argv[1]); 
			exit(0); 
		} else {
			fprintf(_OUTPUT_FILE, line); 
			continue; 
		} 
	} 
	free(line); 

	/* 
	 * Read and check each halo's mass. Allocate memory for a double pointer 
	 * which will get overwritten for each line. 
	 */ 
	double *halo = (double *) malloc (_DIMENSION_ * sizeof(double)); 
	do {
		if (read_line(_INPUT_FILE_, halo, _DIMENSION_)) {
			/* read_line returns 1 at EOF, 0 otherwise */ 
			break; 
		} else { 
			/* If this halo is above the resolution limit */ 
			if (log10(halo[_MASS_COLUMN]) >= _MIN_LOG_MASS_) {
				/* Write it to the output file */ 
				for (i = 0; i < _DIMENSION_; i++) {
					fprintf(_OUTPUT_FILE_, "%lf\t", halo[i]); 
				} 
				fprintf(_OUTPUT_FILE_, "\n"); 
				printf("\r%d halos processed", i + 1); 
			} else {
				continue; 
			} 
		} 
	} while (halo != NULL); 
	printf("\n"); 
	free(halo); 

	return 1; 

}

/* 
 * Set the global variables from the command line input. 
 * 
 * Parameters 
 * ========== 
 * argc: 		The number of command line arguments. This should always be 7. 
 * argv: 		The command line arguments themselves. 
 */ 
static void set_globals(int argc, char **argv) {

	if (argc != 7) { 
		/* Check that there were 4 command line arguments passed. */ 
		printf("Error: incorrect number of command line arguments: %d. ", argc); 
		printf("Must be 6.\n"); 
		exit(0); 
	} else { 
		/* Open the files and check for failed openings */ 
		_INPUT_FILE 		= fopen(argv[1], "r"); 
		_OUTPUT_FILE_ 		= fopen(argv[2], "w"); 
		if (_INPUT_FILE_ == NULL) {
			printf("Error: Couldn't open file: %s\n", argv[1]); 
			exit(0); 
		} else if (_OUTPUT_FILE_ == NULL) {
			printf("Error: Couldn't open file: %s\n", argv[2]); 
			exit(0); 
		} else {} 
		/* Assign the mass mass information */ 
		_MIN_LOG_MASS_ 		= atof(argv[3]); 
		_MASS_COLUMN_ 		= atoi(argv[4]); 
		_HEADER_LENGTH_ 	= atoi(argv[5]); 
		_DIMENSION_ 		= atoi(argv[6]); 
	}

}





