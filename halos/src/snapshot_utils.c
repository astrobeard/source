
#include <stdlib.h> 
#include "snapshot.h" 

/* 
 * Frees up the memory stored within a SNAPSHOT 
 * 
 * Parameters 
 * ========== 
 * snap: 		The SNAPSHOT struct itself 
 * 
 * header: snapshot.h 
 */ 
extern void free_snapshot(SNAPSHOT *snap) {

	free(snap -> data); 

}


