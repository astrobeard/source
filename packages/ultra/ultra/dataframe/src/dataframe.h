/* 
 * This is the header file associated with the dataframe class 
 */ 

#ifndef DATAFRAME_H 
#define DATAFRAME_H 

/* 
 * The dataframe struct. This is the struct that will store the data read in 
 * from a halo catalog. 
 * 
 * Fields 
 * ====== 
 * data: 		The data itself - a double pointer to it 
 * num_rows: 	The number of elements in the first dimension of indexing 
 * num_cols: 	The number of elements in the second dimension of indexing 
 */ 
typedef struct dataframe {

	double **data; 
	long num_rows; 
	int num_cols; 

} DATAFRAME; 

/* 
 * Allocates memory for a dataframe struct and returns the pointer. 
 * 
 * source: dataframe_utils.c 
 */ 
extern DATAFRAME *dataframe_initialize(void); 


/* 
 * Allocates memory for an array of dataframes and returns the pointer. 
 * 
 * Parameters 
 * ========== 
 * n: 		The number of dataframes to put in the array. 
 * 
 * source: dataframe_utils.c 
 */ 
extern DATAFRAME **dataframe_array_initialize(int n); 

/* 
 * Frees the memory storing both the data attribute and the dataframe struct 
 * itself. 
 * 
 * source: dataframe_utils.c 
 */ 
extern void free_dataframe(DATAFRAME *df); 

/* 
 * Frees up the memory stored in an array of dataframes. 
 * 
 * Parameters 
 * ========== 
 * df: 		The array of dataframes to free up 
 * n: 		The number of dataframes in the array 
 * 
 * source: dataframe_utils.c 
 */ 
extern void free_dataframe_array(DATAFRAME **df, int n); 





/* --------------------------- FILE I/O FUNCTIONS --------------------------- */ 

/* 
 * Reads in the data from a file and stores it in a dataframe object's data 
 * field. 
 * 
 * Parameters 
 * ========== 
 * df: 			A pointer to the dataframe to populate 
 * file:		The name of the file as a character pointer 
 * comment: 	The commenting character 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure reading the file 
 * 
 * source: dataframe_io.c 
 */
extern int populate_from_file(DATAFRAME *df, char *file, char comment); 









/* ---------------------------- DATAFRAME SUBS ---------------------------- */ 

/* 
 * Takes a column from the data and returns a double pointer to it 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to take the column from 
 * column: 		The column number to take 
 * 
 * Returns 
 * ======= 
 * Type *double :: The column'th element of each row in the dataframe 
 * NULL if the column number is not allowed 
 * 
 * source: dataframe_subs.c 
 */ 
extern double *dfcolumn(DATAFRAME df, int column); 

/* 
 * Determine the minimum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value from 
 * 
 * Returns 
 * ======= 
 * Type double :: The minimum value stored in that column of the data 
 * NULL if the column number is not allowed 
 * 
 * source: dataframe_subs.c 
 */ 
extern double dfcolumn_min(DATAFRAME df, int column); 

/* 
 * Determine the maximum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The maximum value stored in that column of the data 
 * NULL if the column number is not allowed 
 * 
 * source: dataframe_subs.c 
 */ 
extern double dfcolumn_max(DATAFRAME df, int column); 

/* 
 * Determine the sum of the values stored in a column of the dataframe 
 * 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The sum of the values in that column 
 * NULL if the column number is not allowed 
 * 
 * source: dataframe_subs.c 
 */ 
extern double dfcolumn_sum(DATAFRAME df, int column); 

/* 
 * Determine the arithmetic mean of the value stored in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * 
 * Returns 
 * ======= 
 * Type double :: The arithmetic mean of the data in that column 
 * NULL if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
extern double dfcolumn_mean(DATAFRAME df, int column); 

/* 
 * Determine the median of a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the median of 
 * 
 * Returns
 * ======= 
 * Type double :: The median of the data in that column 
 * 0 if the column number is not allowed 
 * 
 * header: dataframe.h 
 */ 
// extern double dfcolumn_median(DATAFRAME df, int column); 





/* ---------------------------- SIEVE FUNCTIONS ---------------------------- */ 

/* 
 * Filters the data based on a given condition on a given column and returns 
 * a new dataframe object. 
 * 
 * Parameters 
 * ========== 
 * df: 					The dataframe holding the data to filter 
 * column: 				The column to impose the filter on 
 * value: 				The value to test on 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 
 * Returns 
 * ======= 
 * A new dataframe whose data attribute contains only the rows which satisfy 
 * the condition df[row][column] ?(relational_code) value. 
 * 
 * NULL if the relational_code is not recognized. 
 * 
 * source: dataframe_sieve.c 
 */ 
extern DATAFRAME *sieve_new_frame(DATAFRAME df, int column, int value, 
	int relational_code); 

/* 
 * Filters the data based on a given condition and removes all other data 
 * from the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 					The dataframe holding the data to filter 
 * column: 				The column to impose the filter on 
 * value: 				The value to test on 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 
 * Returns 
 * ======= 
 * an int: 0 if successful, 1 if failure. 
 * 
 * source: dataframe_sieve.c 
 */ 
extern int sieve_same_frame(DATAFRAME *df, int column, int value, 
	int relational_code); 







/* --------------------------- SORTING FUNCTIONS --------------------------- */ 

/* 
 * Sorts the data from least to greatest based on the values in a given 
 * column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to take the index of 
 * 
 * Returns 
 * ======= 
 * Type DATAFRAME :: A new dataframe with the same rows, but sorted least to 
 * greatest according to the column'th value in each row. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *dfcolumn_order(DATAFRAME df, int column); 

/* 
 * Determine the number of rows that fall within specified bins (i.e. a 
 * histogram) based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to get counts based on 
 * binspace: 	The binspace to sort based on 
 * num_bins: 	The number of bins in the binspace. This should be one less 
 * 				than the number of values in the binspace array. 
 * 
 * Returns 
 * ======= 
 * Type *long :: The counts within each bin 
 * 
 * header: dataframe.h 
 */ 
extern long *hist(DATAFRAME df, int column, double *binspace, long num_bins); 





#endif /* DATAFRAME_H */ 

