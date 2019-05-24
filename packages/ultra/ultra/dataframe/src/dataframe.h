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
	int *columns, int num_cols); 









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
 * ptr: 		A pointer to put the minimum value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * source: dataframe_subs.c 
 */ 
extern int dfcolumn_min(DATAFRAME df, int column, double *ptr); 

/* 
 * Determine the maximum value in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value from 
 * ptr: 		A pointer to put the maximum value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * source: dataframe_subs.c 
 */ 
extern int dfcolumn_max(DATAFRAME df, int column, double *ptr); 

/* 
 * Determine the sum of the values stored in a column of the dataframe 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to take the minimum value of 
 * ptr: 		A pointer to put the sum in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure
 * 
 * source: dataframe_subs.c 
 */ 
extern int dfcolumn_sum(DATAFRAME df, int column, double *ptr); 

/* 
 * Determine the arithmetic mean of the value stored ina column of the 
 * dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column index to find the mean value of 
 * ptr: 		A pointer to put the mean value in 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * source: dataframe_subs.c 
 */ 
extern int dfcolumn_mean(DATAFRAME df, int column, double *ptr); 

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

/* 
 * Determine the standard deviation of a column of the data. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column:	 	The column number to find the standard deviation of 
 * ptr: 		A pointer to put the standard deviation into 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * source: dataframe_subs.c 
 */ 
extern int dfcolumn_std(DATAFRAME df, int column, double *ptr); 





/* ---------------------------- SIEVE FUNCTIONS ---------------------------- */ 

/* 
 * Filter the dataset based on some condition applied to the values stored in 
 * a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 					A pointer to the dataframe to modify 
 * column: 				The column number to filter based on 
 * value: 				The value to compare to for filtering 
 * relational_code:		1 for < 
 * 						2 for <= 
 *						3 for = 
 * 						4 for >= 
 * 						5 for > 
 * 						6 for != 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * source: dataframe_sieve.c 
 */ 
extern int sieve(DATAFRAME *df, int column, double value, int relational_code); 








/* --------------------------- SORTING FUNCTIONS --------------------------- */ 

/* 
 * Splits the data into equal number bins based on the data in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column number to sort based on 
 * num_subs:	The number of subsamples to take 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **equal_number_samples(DATAFRAME df, int column, 
	long num_subs); 

/* 
 * Sorts the dataframe based into bins based on the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column number to sort based on 
 * binspace: 	The bin-edges to sort with 
 * num_bins: 	The number of bins. This should always be one less than the 
 * 				number of elements in the binspace array. 
 * 
 * Returns 
 * ======= 
 * Type **DATAFRAME :: An array of dataframes whose elements correspond to the 
 * data belonging to that bin based on the values in a given column. 
 * 
 * header: dataframe.h 
 */ 
// extern DATAFRAME **sort(DATAFRAME df, int column, double *binspace, 
// 	long num_bins); 

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
 * Determine the number of data points that fall within specified bin (i.e. 
 * a histogram) based on the values in a given column of the dataframe. 
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
 * 0 always. If it returns anything else, there was an internal error. 
 * 
 * header: dataframe.h 
 */ 
extern int hist(DATAFRAME df, int column, double *binspace, long num_bins, 
	long *counts);  





#endif /* DATAFRAME_H */ 

