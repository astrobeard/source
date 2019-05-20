
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 

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

	DATAFRAME *ordered_x = dfcolumn_order(*df, 3); 

	int i, j; 
	for (i = 0; i < 10; i++) {
		for (j = 0; j < df.num_cols; j++) {
			printf("ordered_x[%d][%d] = %lf\n", i, j, (*ordered_x).data[i][j]); 
		}
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

	free_dataframe(ordered_x); 
	free_dataframe(df); 
	return 0; 

}


