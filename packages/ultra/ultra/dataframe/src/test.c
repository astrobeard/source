
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 

/* 
 * Currently running tests on dataframe file I/O. 
 */ 
int main(void) { 

	DATAFRAME *df = dataframe_initialize(); 
	if (populate_from_file(df, 
		"/Users/astrobeard/Work/Research/data/Vishnu/Vishnu_z0p0.dat", 
		'#')) { 
		return 1; 
	} else {} 

	int i, j; 
	for (i = 0; i < 10; i++) {
		for (j = 0; j < (*df).num_cols; j++) {
			printf("df.data[%d][%d] = %lf\n", i, j, (*df).data[i][j]); 
		}
	}

	free_dataframe(df); 
	return 0; 

}


