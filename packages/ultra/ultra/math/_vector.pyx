# cython: language_level=3, boundscheck = False 
"""
This is the source code for the ultra vector class 
"""

# python functions 
from .._globals import _DIRECTORY_ 
from .._globals import _VERSION_ERROR_ 
import warnings  
import numbers 
import sys 
import os 
if sys.version_info[:2] < (3, 5): 
	_VERSION_ERROR_() 
else: 
	pass 
try: 
	ModuleNotFoundError 
except NameError: 
	ModuleNotFoundError = ImportError 
try: 
	import numpy as _np 
except (ModuleNotFoundError, ImportError): 
	pass 
try: 
	import pandas as _pd 
except (ModuleNotFoundError, ImportError): 
	pass 

__all__ = ["vector"] 

# C functions 
from libc.stdlib cimport malloc, free 
cdef extern from "./src/vector.h": 
	ctypedef struct VECTOR: 
		double *vector 
		int dimension 

	VECTOR *vector_initialize() 
	void vector_free(VECTOR *v) 
	int vector_set_dimension(VECTOR *v, int d) 
	int vector_set_vector(VECTOR *v, double *arr) 
	double vector_magnitude(VECTOR v) 
	VECTOR *vector_direction(VECTOR v) 

cdef double *double_ptr_from_pylist(pylist): 
	"""
	Obtain a double pointer array from a python list 
	""" 
	cdef double *ptr = <double *> malloc (len(pylist) * sizeof(double)) 
	if ptr is NULL: 
		raise MemoryError("Memory error in double_ptr_from_pylist") 
	else: 
		for i in range(len(pylist)): 
			ptr[i] = pylist[i]
		return ptr 

def __copy_array_like_object(arg): 
	"""
	Takes an array-like object and returns a copy of it as a native python 
	list. 

	Parameters 
	========== 
	arg :: array-like 
		Some sort of array-like object. 

	Returns 
	======= 
	A copy of the object in a python list 
	"""
	if "numpy" in sys.modules and isinstance(arg, _np.ndarray): 
		# Turn a numpy array into a list 
		copy = arg.tolist()[:] 
	elif "pandas" in sys.modules and isinstance(arg, _pd.DataFrame): 
		# Turn a pandas DataFrame into a list 
		copy = [i[0] for i in arg.values.tolist()][:] 
	elif type(arg) in [list, tuple]: 
		# pull a copy if it's native python 
		copy = arg[:] 
	else: 
		raise TypeError("Must be an array-like object. Got: %s" % (type(arg))) 

	return copy 

cdef class vector(object): 

	cdef VECTOR *_cvector 
	cdef VECTOR *_dummy 

	def __init__(self, array): 
		copy = __copy_array_like_object(array) 
		self._cvector = vector_initialize() 
		if vector_set_dimension(self._cvector, len(copy)): 
			raise SystemError("Internal Error") 
		elif vector_set_vector(self._cvector, double_ptr_from_pylist(copy)): 
			raise SystemError("Internal Error") 
		else: 
			pass 

	def __repr__(self): 
		rep = "<" 
		for i in self.vector[:-1]: 
			rep += "%g, " % (i) 
		rep += "%g>" % (self.vector[-1]) 
		return rep 

	def __str__(self): 
		return self.__repr__() 

	def __enter__(self): 
		return self 

	def __exit__(self, exc_type, exc_value, exc_tb): 
		return exc_value == None 

	def __del__(self): 
		vector_free(self._cvector) 

	@property 
	def vector(self): 
		return tuple(
			[self._cvector.vector[i] for i in range(self._cvector.dimension)]
		) 

	@vector.setter 
	def vector(self, array): 
		copy = __copy_array_like_object(array) 
		vector_free(self._cvector) 
		self._cvector = vector_initialize() 
		if vector_set_dimension(self._cvector, len(copy)): 
			raise SystemError("Internal Error") 
		elif vector_set_vector(self._cvector, double_ptr_from_pylist(copy)): 
			raise SystemError("Internal Error") 
		else: 
			pass 

	@property 
	def magnitude(self): 
		"""
		The magnitude (i.e. norm) of the vector: the square root of the sum 
		of the components squared. 
		""" 
		return vector_magnitude(self._cvector[0]) 

	@property 
	def direction(self): 
		"""
		A unit vector pointing in the same direction as this vector. 
		""" 
		self._dummy = vector_direction(self._cvector[0]) 
		v = tuple([self._dummy.vector[i] for i in range(self._dummy.dimension)]) 
		vector_free(self._dummy) 
		return vector(v) 



