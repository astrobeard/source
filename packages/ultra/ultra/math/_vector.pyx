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
	VECTOR *vector_scalar_multiplication(VECTOR v, double scalar) 
	VECTOR *vector_addition(VECTOR v1, VECTOR v2) 
	double vector_dot_product(VECTOR v1, VECTOR v2) 
	VECTOR *vector_cross_product(VECTOR v1, VECTOR v2) 

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

cdef class vector: 

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

	def __getitem__(self, key): 
		if isinstance(key, numbers.Number) and key % 1 == 0: 
			key = int(key) 
			if 0 <= key < self._cvector.dimension: 
				return self._cvector.vector[key] 
			else: 
				raise IndexError("Index out of range: %d" % (key)) 
		else: 
			raise TypeError("Index must be of type int. Got: %s" % (type(key))) 

	def __setitem__(self, key, value): 
		if isinstance(key, numbers.Number) and key % 1 == 0: 
			key = int(key) 
			if 0 <= key < self._cvector.dimension: 
				if isinstance(value, numbers.Number): 
					self._cvector.vector[key] = value 
				else: 
					raise TypeError("""Vector component must be numerical. \
Got: %s""" % (type(value))) 
			else: 
				raise IndexError("Index out of range: %d" % (key)) 
		else: 
			raise TypeError("Index must be of type int. Got: %s" % (type(key))) 

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

	def __pos__(self): 
		return self 

	def __neg__(self): 
		self._dummy = vector_scalar_multiplication(self._cvector[0], -1) 
		v = tuple([self._dummy.vector[i] for i in range(self._dummy.dimension)]) 
		vector_free(self._dummy) 
		return vector(v) 

	def __mul__(self, other): 
		if isinstance(other, numbers.Number): 
			return self.__scalar_multiplication(other) 
		elif isinstance(other, vector): 
			return self.__dot_product(other) 
		else: 
			raise TypeError("Can only multiply with scalar or vector. Got: %s" % (
				type(other))) 

	def __pow__(self, other, what): 
		if what != None: 
			raise TypeError("Cannot take modulo of cross product") 
		else: 
			pass 
		if isinstance(other, vector): 
			if len(other.vector) != 3: 
				raise ValueError("Can only take cross product in 3 dimensions.") 
			else: 
				return self.__cross_product(other) 
		else: 
			raise TypeError("""Can only take cross product with another vector. \
Got: %s""" % (type(other))) 

	def __cross_product(self, vector other): 
		cdef VECTOR _other = other._cvector[0] 
		self._dummy = vector_cross_product(self._cvector[0], _other) 
		v = tuple([self._dummy.vector[i] for i in range(self._dummy.dimension)]) 
		vector_free(self._dummy) 
		return vector(v) 

	def __dot_product(self, vector other): 
		cdef VECTOR _other = other._cvector[0]
		return vector_dot_product(self._cvector[0], _other)  

	def __scalar_multiplication(self, other):
		self._dummy = vector_scalar_multiplication(self._cvector[0], other) 
		v = tuple([self._dummy.vector[i] for i in range(self._dummy.dimension)]) 
		vector_free(self._dummy) 
		return vector(v) 

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



