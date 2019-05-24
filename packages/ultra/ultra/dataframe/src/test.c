
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "dataframe.h" 

/* 
 * Currently running tests on dataframe I/O.  
 */ 
int main(void) { 

	int x = 0, *ptr = &x; 

	*ptr = 3; 
	printf("x = %d\n", x); 

	// free_dataframe(df); 
	return 0; 

}


