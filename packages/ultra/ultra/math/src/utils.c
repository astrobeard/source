
#include "utils.h" 

/* 
 * Determine the absolute value of x 
 * 
 * Parameters 
 * ========== 
 * x: 		The value itself 
 * 
 * Returns 
 * ======= 
 * sign(x) * x 
 * 
 * header: utils.h 
 */ 
extern double _absval(double x) {

	return _sign(x) * x; 

} 

/* 
 * Determine the sign of a double 
 * 
 * Parameters 
 * ========== 
 * x: 		The value itself 
 * 
 * Returns 
 * ======= 
 * 1 if x >= 0, -1 otherwise 
 * 
 * header: utils.h 
 */ 
extern int _sign(double x) { 

	return (x >= 0) - (x < 0); 

}


