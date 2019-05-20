/* 
 * This is the header file associated with the dataframe class 
 */ 

#ifndef DATAFRAME_H 
#define DATAFRAME_H 

#define max(a, b) ({ \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a > _b ? _a : _b; \
}) 

#define min(a, b) ({ \
	__typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
	_a < _b ? _a : _b; \
}) 

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


/* ---------------------------- DATAFRAME SUBS ---------------------------- */ 

/* 
 * Determine the arithmetic mean of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the mean of 
 * 
 * Returns 
 * =======
 * Type double: The mean of the given column number 
 * 
 * source: dataframe_subs.c 
 */ 
extern double column_mean(DATAFRAME df, int column); 

/* 
 * Determines the minimum of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the minimum of 
 * 
 * Returns 
 * ======= 
 * Type double: The minimum value 
 * 
 * source: dataframe_subs.c 
 */ 
extern double column_min(DATAFRAME df, int column); 

/* 
 * Determines the maximum of a given column of the dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe itself 
 * column: 		The column number to find the maximum of 
 * 
 * Returns 
 * ======= 
 * Type double: The maximum value 
 * 
 * header: dataframe.h 
 */ 
extern double column_max(DATAFRAME df, int column); 






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
 * Generates equal number samples from least to greatest based on the values 
 * within a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe to sort 
 * column: 			The column to sort based on 
 * num_bins: 		The number of bins to sort into 
 * 
 * Returns 
 * ======= 
 * Type: **DATAFRAME. An array of dataframes sorted into equal number bins from 
 * least to greatest based on a column number. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **equal_number_samples(DATAFRAME df, int column, 
	int num_bins); 

/* 
 * Obtain counts within a specified binspace (i.e. histogram counts) based on 
 * the values in a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe holding the data 
 * column: 			The column to sort by 
 * binspace: 		A pointer to the histogram bin edges 
 * num_bins: 		The number of bins. This is the number of elements in the 
 * 					binspace array minus 1. 
 * 
 * Returns 
 * ======= 
 * Type: *long. The counts within each bin. 
 * 
 * source: dataframe_sorting.c 
 */ 
extern long *histogram(DATAFRAME df, int column, double *binspace, 
	int num_bins); 

/* 
 * Sorts the data within the dataframe based on a given column from least to 
 * greatest and returns a new dataframe. 
 * 
 * Parameters 
 * ========== 
 * df: 			The dataframe to sort 
 * column: 		The column to sort based on 
 * 
 * Returns 
 * ======= 
 * A dataframe whose data are sorted. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME *rank_by_column(DATAFRAME df, int column); 

/* 
 * Sorts the data within a dataframe into a given binspace based on the 
 * values within a given column. 
 * 
 * Parameters 
 * ========== 
 * df: 				The dataframe to sort 
 * column: 			The column to sort based on 
 * binspace: 		The binspace to sort the data into 
 * num_bins: 		The number of bins. This is the number of elements in the 
 * 					binspace array minus 1. 
 * 
 * Returns 
 * ======= 
 * Type: **DATAFRAME. The array of dataframes that hold the data points that 
 * lie in each bin. 
 * 
 * header: dataframe.h 
 */ 
extern DATAFRAME **sort_by_bins(DATAFRAME df, int column, double *binspace, 
	int num_bins); 






#endif /* DATAFRAME_H */ 

