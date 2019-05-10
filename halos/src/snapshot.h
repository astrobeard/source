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
 * source: snapshot_io.h 
 */
extern int populate_data_from_file(SNAPSHOT *snap, char *file, char comment); 



#endif /* SNAPSHOT_H */ 

