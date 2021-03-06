# cython: language_level=3, boundscheck = False 
"""
This code wraps the dataframe source code implemented in c in src/. 
"""

# Python functions 
from .._globals import _DIRECTORY_ 
from .._globals import _VERSION_ERROR_ 
import math as m 
import warnings 
import numbers 
import inspect 
import sys 
import os 
try: 
	ModuleNotFoundError 
except NameError: 
	ModuleNotFoundError = ImportError 
try: 
	# NumPy compatible but not NumPy dependent 
	import numpy as _np 
except (ImportError, ModuleNotFoundError): 
	pass 
try: 
	# Pandas compatible but not Pandas dependent 
	import pandas as _pd 
except (ImportError, ModuleNotFoundError): 
	pass 
if sys.version_info[:2] < (3, 5): 
	_VERSION_ERROR_() 
else: 
	pass 

# C functions 
from ctypes import * 
from libc.stdlib cimport malloc, free 
clib = cdll.LoadLibrary("%sdataframe/src/dataframe.so" % (_DIRECTORY_)) 

# cdef extern from "./src/dataframe.h": 
# 	ctypedef struct DATAFRAME: 
# 		pass 
# 	DATAFRAME *dataframe_initialize() 
# 	DATAFRAME **dataframe_array_initialize(int n) 

# cdef DATAFRAME **get_dataframe_array(int n): 
# 	return dataframe_array_initialize(n) 

# cpdef mirrorDATAFRAME(DATAFRAME df): 
# 	x = __dataframe() 
# 	x.data = df.data 
# 	x.num_rows = df.num_rows 
# 	x.num_cols = df.num_cols 
# 	return x 

class __dataframe(Structure): 
	"""
	Wraps the C structure version of the dataframe 
	"""
	_fields_ = [
		("data", POINTER(POINTER(c_double))), 
		("num_rows", c_long), 
		("num_cols", c_int) 
	] 

class dataframe(object): 

	"""
	A case-insensitive data storage object with analysis subroutines written 
	in C. 
	""" 

	def __init__(self, arg, **kwargs): 
		self.__mirror = __dataframe() 
		if isinstance(arg, str):
			self.__populate_from_file(arg, **kwargs) 
		elif isinstance(arg, __dataframe): 
			self.__mirror = arg 
			if "labels" in kwargs.keys(): 
				self.__labels = kwargs["labels"]  
			else: 
				raise SystemError("Internal Error") 
		else: 
			raise TypeError("dataframe.__init__ got invalid type: %s" % (
				type(arg))) 

	def __call__(self, key): 
		return self.__getitem__(key) 

	def __getitem__(self, key): 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				return [self.__mirror.data[i][self.__labels.index(
					key.lower())] for i in range(self.__mirror.num_rows)] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		elif isinstance(key, numbers.Number) and key % 1 == 0: 
			if 0 <= key < self.__mirror.num_rows: 
				return [self.__mirror.data[key][i] for i in range(
					self.__mirror.num_cols)] 
			elif -1 * self.__mirror.num_rows < key < 0: 
				key = -1 * key - 1 # The row number to return 
				return [self.__mirror.data[key][i] for i in range(
					self.__mirror.num_cols)] 
			else: 
				raise ValueError("Key index out of range. Got: %d." % (key)) 
		else: 
			raise TypeError("""Dataframe key must be of type int or str. \
Got: %s""" % (type(key))) 

	def __setitem__(self, key, value): 
		if isinstance(key, str): 
			copy = self.__copy_array_like_object(value, "to __setitem__") 
			if all(map(lambda x: isinstance(x, numbers.Number), copy)): 
				if len(copy) == self.__mirror.num_rows: 
					ptr = self.__mirror.num_rows * c_double 
					if key.lower() in self.__labels: 
						if clib.dfcolumn_modify(
							byref(self.__mirror), 
							ptr(*copy[:]), 
							c_int(self.__labels.index(key.lower()))
						): 
							raise SystemError("Internal Error.") 
						else: 
							pass 
					else: 
						if clib.dfcolumn_new(
							byref(self.__mirror), 
							ptr(*copy)
						): 
							raise SystemError("Internal Error.") 
						else: 
							self.__labels = (*self.__labels, key.lower()) 
				else: 
					raise ValueError("""Array length mismath. Got: %d. \
Must be: %d""" % (len(copy), self.__mirror.num_rows)) 
			else: 
				raise TypeError("Non-numerical value detected.") 
		else: 
			raise TypeError("Dataframe keys must be of type str. Got: %s" % (
				type(key))) 

	def __repr__(self): 
		rep = ["dataframe{\n", "\t\t"] 
		for i in self.__labels: 
			rep[1] += "%s\t\t" % (i) 
		rep[1] += "\n" 
		rep.append("\t\t") 
		for i in self.__labels: 
			for j in range(len(i)): 
				rep[2] += "=" 
			rep[2] += "\t\t"
		rep[2] += "\n" 
		if self.__mirror.num_rows > 15: 
			for i in range(5): 
				rep.append("%12s ::\t" % (i)) 
				for j in range(len(self.__labels)): 
					rep[-1] += "%e\t" % (self.__mirror.data[i][j]) 
				rep[-1] += "\n" 
			rep.append("\t...\t") 
			for i in range(len(self.__labels)): 
				rep[-1] += "...\t\t" 
			rep[-1] += "\n" 
			for i in range(5)[::-1]: 
				rep.append("%12s ::\t" % (self.__mirror.num_rows - i - 1)) 
				for j in range(len(self.__labels)): 
					rep[-1] += "%e\t" % (
						self.__mirror.data[self.__mirror.num_rows - i - 1][j]) 
				rep[-1] += "\n" 
			rep.append("}") 
		else: 
			for i in range(self.__mirrow.num_rows): 
				rep.append("%12s ::\t" % (i)) 
				for j in range(len(self.__labels)): 
					rep[-1] += "%e\t" % (self.__mirror.data[i][j]) 
				rep[-1] += "\n" 
			rep.append("}") 
		return "".join(rep) 

	def __str__(self): 
		return self.__repr__() 

	def __enter__(self): 
		"""
		Opens a with statement 
		"""
		return self 

	def __exit__(self, exc_type, exc_value, exc_tb): 
		"""
		Raise all exceptions inside with statements 
		"""
		return exc_value == None 

	def __del__(self): 
		del self.__mirror 
		del self.__labels 

	@property 
	def size(self): 
		"""
		The (length, width) of the dataframe. This is the number of data points 
		as the first component of a tuple and the dimensionality of the data 
		as the second component of a tuple. 
		""" 
		return (self.__mirror.num_rows, self.__mirror.num_cols) 

	def keys(self): 
		"""
		Obtain the dataframe keys in their lower-case format 

		Returns 
		======= 
		keys :: list [elements of type str]
			The strings which serve as case-insensitive dataframe keys 
		"""
		return self.__labels 

	def __populate_from_file(self, filename, columns = None, labels = None, 
		comment = '#'): 
		"""
		Populate the dataframe with data stored in a given file. 
		"""	
		if not isinstance(filename, str): 
			raise TypeError("filename must be of type str. Got: %s" % (
				type(filename))) 
		elif not isinstance(columns, list): 
			raise TypeError("""\
Keyword arg columns must be of type list. Got: %s""" % (type(columns))) 
		elif not isinstance(labels, list): 
			raise TypeError("""\
Keyword arg labels must be of type list. Got: %s""" % (type(labels))) 
		elif not all(map(lambda x: isinstance(x, numbers.Number), columns)): 
			raise TypeError("Non-numerical value detected in columns.") 
		elif not all(map(lambda x: isinstance(x, str), labels)): 
			raise TypeError("Non-string object detected in labels.") 
		elif not all(map(lambda x: x % 1 == 0, columns)): 
			raise ValueError("Columns must contain only int-like numbers.") 
		elif not os.path.exists(filename): 
			raise IOError("File not found: %s" % (filename)) 
		else: 
			if len(columns) == len(labels): 
				columns = [int(i) for i in columns] 
				ptr = len(columns) * c_int 
				if clib.populate_from_file(
					byref(self.__mirror), 
					filename.encode("latin-1"), 
					comment.encode("latin-1"), 
					ptr(*columns[:]), 
					c_int(len(columns)) 
				):
					raise IOError("Error reading file: %s" % (filename)) 
				else: 
					self.__labels = tuple([i.lower() for i in labels])  
			else: 
				raise ValueError("""\
Keyword args columns and labels must be of equal length. columns: %d \
labels: %d""" % (len(columns), len(labels))) 

	def min(self, key): 
		"""
		Determine the minimum value of a given quantity in the data. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the minimum value of 

		Returns 
		======= 
		minimum :: float 
			The minimum value itself 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		"""
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_min(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x 
				): 
					raise SystemError("Internal Error") 
				else:
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def max(self, key): 
		"""
		Determine the maximum value of a given quantity in the data. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the maximum value of 

		Returns 
		======= 
		maximum :: float 
			The maximum value itself 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_max(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x
				): 
					raise SystemError("Internal Error") 
				else: 
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 


	def sum(self, key): 
		"""
		Determine the sum of a given quantity for all data points. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the sum of 

		Returns 
		======= 
		total :: float 
			The maximum value itself 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_sum(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x
				): 
					raise SystemError("Internal Error") 
				else: 
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def mean(self, key): 
		"""
		Determine the arithmetic mean of a given quantity for all data points. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the mean of 

		Returns 
		======= 
		avg :: float 
			The arithmetic mean of that quantity across all data points. 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		"""	
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_mean(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x
				): 
					raise SystemError("Internal Error") 
				else: 
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def median(self, key): 
		"""
		Determine the median of a given quantity for all data points. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the median of 

		Returns 
		======= 
		med :: float 
			The median value of that quantity across all data points 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_median(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x
				): 
					raise SystemError("Internal Error") 
				else: 
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def std(self, key): 
		"""
		Determine the standard deviation of a given quantity for all data 
		points. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to find the mean of 

		Returns 
		======= 
		dev :: float 
			The standard deviation of the data 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		"""
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				ptr = 1 * c_double 
				x = ptr(*[0]) 
				if clib.dfcolumn_std(
					self.__mirror, 
					c_int(self.__labels.index(key.lower())), 
					x
				): 
					raise SystemError("Internal Error") 
				else: 
					return x[0] 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def sieve(self, key, relation, value): 
		"""
		Filter the data based on the values stored in a given column. The 
		data that pass the filter will be those that satisfy the relation 
		data[key] relation value 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the quantity to filter based on 
		relation :: str 
			Either '>', '>=', '=', '==', '!=', <=', or '<' 
		value :: real number 
			A reference value to filter based on 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
			:: value is not a real number 
			:: relation is not of type str 
		ValueError :: 
			:: relation is not a valid string 
		"""	
		relational_codes = {
			"<": 		1, 
			"<=": 		2, 
			"=": 		3, 
			"==": 		3, 
			">=": 		4, 
			">": 		5, 
			"!=": 		6 
		} 

		if isinstance(key, str): 
			if isinstance(value, numbers.Number): 
				if isinstance(relation, str): 
					if key.lower() in self.__labels: 
						if relation in relational_codes.keys(): 
							mirror = __dataframe() 
							if clib.sieve(
								self.__mirror, 
								byref(mirror), 
								c_int(self.__labels.index(key.lower())), 
								c_double(value), 
								c_int(relational_codes[relation])
							): 
								raise SystemError("Internal Error") 
							else: 
								return dataframe(mirror, labels = self.__labels) 
						else: 
							raise ValueError("Unrecognized relation: %s" % (
								relation)) 
					else: 
						raise KeyError("Unrecognized key: %s" % (key)) 
				else: 
					raise TypeError("relation must be of type str. Got: %s" % (
						type(relation))) 
			else: 
				raise TypeError("value must be a real number. Got: %s" % (
					type(value))) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def sort(self, key, binspace): 
		"""
		Sort the dataframe into bins based on the values in a given column. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the column to sort based on 

		Returns 
		======= 
		frames :: list [elements of type dataframe] 
			A list of dataframe objects whose elements are those which fall 
			into the specified bins 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: An element of binspace is non-numerical 
			:: key is not of type str 
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				copy = self.__copy_array_like_object(binspace, "binspace") 
				if all(map(lambda x: isinstance(x, numbers.Number), copy)): 
					mirrors = (len(copy) - 1) * [None] 
					for i in range(len(mirrors)): 
							mirrors[i] = __dataframe()  
					copy = sorted(copy)[:] 
					for i in range(len(binspace) - 1): 
						edges = [binspace[i], binspace[i + 1]] 
						ptr = 2 * c_double 
						if clib.dfcolumn_bin(
							self.__mirror, 
							byref(mirrors[i]), 
							c_int(self.__labels.index(key.lower())), 
							ptr(*edges[:]) 
						): 
							raise SystemError("Internal Error") 
						else: 
							continue 
					return [dataframe(i, 
						labels = self.__labels) for i in mirrors] 
				else: 
					raise TypeError("Non-numerical value detected in binspace.") 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def equal_number_subsamples(self, key, n): 
		"""
		Generate equal number bins of the data according to the values stored 
		in a given column. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the column to bin based on 
		n :: integer 
			The number of samples to generate 

		Returns 
		======= 
		sorted :: list 
			Dataframe objects in a list where each dataframe contains the data 
			in a given bin. Each dataframe object will be approximately the same 
			size by design, and they will be sorted from least to greatest 
			based on the values in the specified column. 

		Raises 
		====== 
		TypeError :: 
			:: key is not of type str 
			:: n is not an integer 
		ValueError :: 
			:: n <= 0 
		KeyError :: 
			:: key is not recognized by the dataframe 
		""" 
		if not isinstance(key, str): 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 
		elif not key.lower() in self.__labels: 
			raise KeyError("Unrecognized key: %s" % (key)) 
		elif not (isinstance(n, numbers.Number) and n % 1 == 0) :
			raise TypeError("Second argument must be an integer. Got: %s" % (
				type(n))) 
		elif n <= 0: 
			raise ValueError("""Second argument must be larger than zero. \
Got: %d""" % (n)) 
		else: 
			pass 

		# cdef DATAFRAME **mirrors = get_dataframe_array(n) 
		# if clib.equal_number_samples(self.__mirror, mirros, 
		# 	c_int(self.__labels.index(key.lower())), c_int(n)): 
		# 	raise SystemError("Internal Error") 
		# else: 
		# 	results = [dataframe(mirrorDATAFRAME(mirrors[i][0]), 
		# 		labels = self.__labels) for i in range(n)] 
		# 	free(mirrors) 
		# 	return results 

		dummy = dataframe(self.__mirror, labels = self.__labels) 
		dummy.order(key) 
		mirrors = n * [None] 
		for i in range(n): 
			mirrors[i] = __dataframe() 
			if clib.dfcolumn_equal_number_subsample(
				dummy._dataframe__mirror, 
				byref(mirrors[i]), 
				c_int(n), 
				c_int(i)
			): 
				raise SystemError("Internal Error") 
			else: 
				continue 
		del dummy 
		return [dataframe(i, labels = self.__labels) for i in mirrors] 


	def order(self, key): 
		"""
		Sort the dataframe in ascending order based on the data in a given 
		column. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the column to sort based on 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: key is not of type str 
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				if clib.dfcolumn_order(
					byref(self.__mirror), 
					c_int(self.__labels.index(key.lower()))
				): 
					raise SystemError("Internal Error") 
				else: 
					pass 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	def scatter(self, key, value = 68.2): 
		"""
		Measure the dispersion in a given column of the data given a percentage 
		value. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The key to the dataframe to measure the scatter for 
		value :: real number between 0 and 100 
			The percentile range to measure 

		Returns 
		======= 
		lower :: real number 
			A lower bound 
		upper :: real number 
			An upper bound 
		Lower and upper are defined such that the specified percentage of the 
		data points lie between these values, centered on the median. 

		Raises 
		====== 
		TypeError :: 
			:: key is not of type str 
			:: value is not a real number 
		ValueError :: 
			:: value is not between 0 and 100 
		KeyError :: 
			:: key is not in the dataframe 
		""" 
		if isinstance(key, str): 
			if key.lower() in self.__labels: 
				if isinstance(value, numbers.Number): 
					if 0 <= value <= 100: 
						ptr = 2 * c_double 
						x = ptr(*[0, 0][:]) 
						if clib.dfcolumn_scatter(
							self.__mirror, 
							c_int(self.__labels.index(key.lower())), 
							c_double(value / 100), 
							x
						): 
							raise SystemError("Internal Error.") 
						else: 
							return [x[0], x[1]] 
					else: 
						raise ValueError("""Keyword arg 'value' must be between \
0 and 100. Got: %g""" % (value)) 
				else: 
					raise TypeError("""Keyword arg 'value' must be a numerical \
value. Got: %s""" % (type(value))) 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 


	def hist(self, key, binspace): 
		"""
		Determine counts within a given binspace (i.e. a histogram) of the 
		data based on the values stored in a given column. 

		Parameters 
		========== 
		key :: str [case-insensitive] 
			The label for the column to histogram 
		binspace :: array-like [elements are real numbers] 
			The bin-edges to histogram based on 

		Returns 
		======= 
		counts :: list [elements are positive integers] 
			The number of data points whose value falls within the specified 
			bin edges 

		Raises 
		====== 
		KeyError :: 
			:: The label is not recognized by this dataframe 
		TypeError :: 
			:: Any element of binspace is non-numerical 
			:: key is not of type str 
		""" 
		if isinstance(key, str): 
			# if the key is recognized 
			if key.lower() in self.__labels: 
				# Get a copy of the bins and make sure it's all real numbers 
				copy = self.__copy_array_like_object(binspace, "binspace") 
				if all(map(lambda x: isinstance(x, numbers.Number), copy)): 
					# get the counts from C 
					ptr = (len(binspace) - 1) * c_long 
					counts = ptr( *((len(binspace) - 1) * [0]) ) 
					ptr = len(binspace) * c_double 
					binspace = ptr(*sorted(copy)[:]) 
					if clib.hist( 
						self.__mirror, 
						c_int(self.__labels.index(key.lower())), 
						binspace, 
						c_long(len(binspace) - 1l), 
						counts 
					): 
						raise SystemError("Internal Error") 
					else: 
						# return the counts 
						return [counts[i] for i in range(len(binspace) - 1l)] 
				else: 
					raise TypeError("Non-numerical value detected in binspace.") 
			else: 
				raise KeyError("Unrecognized key: %s" % (key)) 
		else: 
			raise TypeError("Key must be of type str. Got: %s" % (type(key))) 

	@staticmethod 
	def __copy_array_like_object(arg, name): 
		"""
		Takes an array like object and returns a copy of it as a native python 
		list. 

		Parameters 
		========== 
		arg :: array-like 
			Some sort of array-like object. 
		name :: str 
			The name of the object, for exception raising purposes 

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
			raise TypeError("""\
Argument %s must be an array-like object. Got: %s""" % (name, type(arg))) 

		return copy 


 

