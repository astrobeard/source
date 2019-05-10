
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "snapshot.h" 

/* 
 * Currently running tests on snapshot file I/O. 
 */ 
int main(void) {

	printf("Initializing snapshot....\n"); 
	SNAPSHOT *snap; 
	printf("Snapshot initialized....\n"); 
	printf("Reading file....\n"); 
	int test = populate_data_from_file(snap, 
		"/Users/astrobeard/Work/Research/data/Vishnu/Vishnu_z0p0.dat", 
		'#'); 
	printf("File read!\n"); 
	printf("snap.num_rows: %ld\n", (*snap).num_rows); 
	printf("snap.num_cols: %d\n", (*snap).num_cols); 

	int i, j; 
	for (i = 0; i < 10; i++) {
		for (j = 0; j < (*snap).num_cols; j++) {
			printf("snap[%d][%d] = %lf\n", i, j, (*snap).data[i][j]); 
		}
	}


	free(snap); 
	return 0; 

}


