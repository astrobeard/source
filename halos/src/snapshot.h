/* 
 * This is the header file associated with the snapshot class 
 */ 

#ifndef SNAPSHOT_H 
#define SNAPSHOT_H 


/* 
 * The snapshot struct. This is the struct that will store the data read in 
 * from a halo catalog. 
 * 
 * Fields 
 * ====== 
 * data: 		The data itself - a double pointer to it 
 * num_rows: 	The number of elements in the first dimension of indexing 
 * num_cols: 	The number of elements in the second dimension of indexing 
 */ 
typedef struct snapshot {

	double **data; 
	long num_rows; 
	int num_cols; 

} SNAPSHOT; 


/* 
 * Reads in the data from a file and stores it in a snapshot object's data 
 * field. 
 * 
 * Parameters 
 * ========== 
 * file:		The name of the file as a character pointer 
 * 
 * source: snapshot_io.c
 */
extern int populate_data_from_file(SNAPSHOT *snap, char *file, char comment); 

/* 
 * Frees up the memory stored within a SNAPSHOT 
 * 
 * Parameters 
 * ========== 
 * snap: 		The SNAPSHOT struct itself 
 * 
 * source: snapshot_utils.c 
 */ 
extern void free_snapshot(SNAPSHOT *snap); 

/* 
 * Emulates python's range function 
 * 
 * Parameters 
 * ========== 
 * start:		The starting value of the resultant array 
 * stop: 		The stopping value of the resultant array 
 * 
 * Returns 
 * ======= 
 * An array of longs containing every value between start and 
 * stop - 1l (inclusive). 
 */ 
extern long *range(long start, long stop); 



#endif /* SNAPSHOT_H */ 

