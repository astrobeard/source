# cython: language_level = 3, boundscheck = False 
"""
Ultra Mathematical Functions 
============================ 
""" 

from .._globals import _DIRECTORY_ 
from .._globals import _VERSION_ERROR_ 
import numbers 
import sys 
import os 
if sys.version_info[:2] < (3, 5): 
	_VERSION_ERROR_() 
else: 
	pass 

from libc.stdlib cimport malloc, free 
cdef extern from "./src/ultramath.h": 
	cdef double _PI 
	cdef double _EE 
	long _factorial(double x) 
	double _sin(double x) 

PI = _PI
EE = _EE 

__all__ = ["sin"]

cpdef sin(double x): 
	cdef double sin_x = _sin(x) 
	result = sin_x 
	return result 

# def sin(x, tolerance = 1.e-3, radians = True): 
# 	""" 
# 	Compute the value of sin(x) to a given precision 

# 	Signature: sin(x, tolerance = 1.e-3, radians = True) 

# 	Parameters 
# 	========== 
# 	x :: real number 
# 		The value to compute the sine of 
# 	tolerance :: real number [default :: 1e-3] 
# 		The maximum fractional tolerance. Must be between 0 and 1. 
# 	radians :: bool [default :: True] 
# 		If True, x is taken to be in radians. If False, x is in degrees. 

# 	Returns 
# 	======= 
# 	sin x :: real number 
# 		Always between -1 and 1 to within the specified numerical tolerance. 
# 		The numerically calculated number of iterations through a sin(x) 
# 		Maclaurin series centered around 0. 

# 	Raises 
# 	====== 
# 	TypeError :: 
# 		:: x is non-numerical 
# 		:: tolerance is non-numerical 
# 	ValueError :: 
# 		:: Tolerance is not between 0 and 1 
# 	RuntimeWarning :: 
# 		:: The value does not converge within specified tolerance  

# 	Notes 
# 	===== 
# 	This function will always terminate after N = 2e8 iterations 
# 	""" 
# 	if not isinstance(x, numbers.Number): 
# 		raise TypeError("First argument must be a real number. Got: %s" % (
# 			type(x))) 
# 	elif not isinstance(tolerance, numbers.Number): 
# 		raise TypeError("""Keyword arg 'tolerance' must be a numerical value. \
# Got: %s""" % (type(tolerance))) 
# 	elif not 0 <= tolerance <= 1: 
# 		raise ValueError("""Keyword arg 'tolerance' must be between 0 and 1. \
# Got: %e""" % (tolerance)) 
# 	elif not radians: 
# 		x *= 180 / PI 
# 	else: 
# 		pass  

# 	cdef double *sin_x = _sin(x, tolerance) 
# 	if sin_x[1] >= tolerance: 
# 		raise RuntimeWarning("Did not converge. Error = %e" % (sin_x[1])) 
# 	else: 
# 		pass 

# 	result = sin_x[0] 
# 	free(sin_x) 
# 	return result 







