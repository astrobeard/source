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
 * header: hlists.h 
 */ 
extern int condense(char *file, char *commenter, char *outfile, double minlogm, 
	int masscol) { 

	/* Debugging */ 
	char comment = '#'; 
	// char comment = commenter[0]; 

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
	long lines = num_lines(file); 
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

	/* 
	 * Allocate memory for a dummy line of data, writing the header to the 
	 * output file. 
	 */ 
	char *line = (char *) malloc (LINESIZE * sizeof(char)); 
	for (i = 0; i < hlen; i++) { 
		if (fgets(line, LINESIZE, in) == NULL) { 
			/* Returns 1 on failure to read the input file */ 
			fclose(in); 
			free(line); 
			return 1; 
		} else {
			fprintf(out, "%s", line); 
		} 
	} 
	free(line); /* free up the dummy line */ 

	double *data; 
	long j, counter = 0l; /* keep track of the number of lines parsed */ 
	for (j = 0l; j < lines - hlen; j++) {
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
				/* Something went wrong */ 
				free(data); 
				fclose(in);
				fclose(out); 
				return 1; 
			} 
		} 

		/* Compare the log10 of the mass to the specified minlogm */ 
		if (log10(data[masscol]) >= minlogm) {
			/* If it's above the resolution limit, write to the output file */ 
			for (i = 0; i < dim; i++) {
				/* 15 digits of precision in doubles ---> save them all */ 
				fprintf(out, "%.15e\t", data[i]); 
			} 
			fprintf(out, "\n"); 
		} else {} 

		free(data); 
		printf("\r%ld of %ld lines processed....", j, lines - hlen); 
	} 
	printf("\n"); 

	fclose(in); 
	fclose(out); 
	return 0; 

} 


