# cython: language_level=3, boundscheck = False 
from libc.stdlib cimport malloc, free 

cdef extern from "./src/calculus.h": 
	ctypedef struct MAPPED_FUNCTION: 
		char *method 
		double *bins 
		double *mapped 
		unsigned long n 
	double evaluate(MAPPED_FUNCTION f) 

cdef double *map_pyfunc(pyfunc, xvals): 
	"""
	Map a python function across a range of x values and store the values in a 
	double pointer with allocated memory. 

	Parameters 
	========== 
	pyfunc :: function 
		The function to evaluate 
	xvals :: list 
		The values to evaluate the function at 

	Returns 
	======= 
	A double pointer to the value of the evaluated function at each of the 
	specified values 
	""" 
	cdef double *evaluated = <double *> malloc (len(xvals) * sizeof(double)) 
	for i in range(len(xvals)): 
		evaluated[i] = pyfunc(xvals[i]) 
	return evaluated 

cdef evaluate_integral(func, a, b, method, tolerance, Nmax): 
	cdef MAPPED_FUNCTION f = MAPPED_FUNCTION() 


def integrate(func, a, b, method = "trapezoid", tolerance = 1.e-3, Nmax = 2e8): 
	"""
	Evaluate the integral of func from the bounds a to b according to a 
	specified method of numerical quadrature and tolerance. 

	Parameters 
	========== 
	func :: function 
		A callable function accepting a real number 
	a :: real number 
		The lower bound of integration 
	b :: real number 
		The upper bound of integration 
	method :: string 
		The method of integration 
	tolerance :: real number 
		The maximum allowed numerical tolerance 
	Nmax :: long integer 
		The maximum number of iterations (included as a failsafe) 
	""" 
	return 0 



