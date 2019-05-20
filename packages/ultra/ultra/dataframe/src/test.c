
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 
#include "utils.h" 

/* 
 * Currently running tests on dataframe subs.  
 */ 
int main(void) { 

	DATAFRAME *df = dataframe_initialize(); 
	if (populate_from_file(df, 
		"/Users/astrobeard/Work/Research/data/Vishnu/Vishnu_z0p0.dat", 
		'#')) { 
		return 1; 
	} else {} 

	double *arr = (double *) malloc (10000 * sizeof(double)); 
	long i; 
	for (i = 0l; i < 10000l; i++) {
		arr[i] = (*df).data[i][3]; 
	} 

	arr = ptr_sort(arr, 10000); 

	for (i = 0l; i < 25l; i++) {
		printf("arr[%ld] = %lf\n", i, arr[i]); 
	}

	// int i, j; 
	// for (i = 0; i < (*df).num_cols; i++) {
	// 	printf("====================\n"); 
	// 	printf("dfcolumn_min(%d) = %lf\n", i, dfcolumn_min(*df, i)); 
	// 	printf("dfcolumn_max(%d) = %lf\n", i, dfcolumn_max(*df, i)); 
	// 	printf("dfcolumn_sum(%d) = %lf\n", i, dfcolumn_sum(*df, i)); 
	// 	printf("dfcolumn_mean(%d) = %lf\n", i, dfcolumn_mean(*df, i)); 
	// 	printf("dfcolumn_median(%d) = %lf\n", i, dfcolumn_median(*df, i)); 
	// 	printf("====================\n"); 
	// }

	free(arr); 
	free_dataframe(df); 
	return 0; 

}


