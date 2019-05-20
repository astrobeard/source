"""
This code wraps the dataframe source code implemented in c in src/. 
"""

import math as m
import warnings 
import numbers 
import inspect 
import sys 
import os 

from ctypes import * 

cdef extern from "./src/dataframe.h":
	int populate_from_file(DATAFRAME *df, char *file, char comment) 
	double column_mean(DATAFRAME df, int column) 
	double column_min(DATAFRAME df, int column) 
	double column_max(DATAFRAME df, int column) 



class dataframe(object): 
	"""
	A case-insensitive data storage object with analysis subroutines. 
	"""

	def __init__(self, x): 
		self.__mirror = __dataframe() 
		if isinstance(x, str): 
			self.__populate_from_file(x) 
		else: 
			raise TypeError("""Dataframe can only be initialize by type str. \
Got: %s""" % (type(x))) 


	def __populate_from_file(self, x): 
		"""
		Populates the dataframe contents from that of a file. 

		Parameters 
		========== 
		x :: str 
			The name of the file (can be full or relative path) 
		""" 
		if isinstance(x, str): 
			# This should always be the case 
			if os.path.exists(x): 
				test = populate_from_file(byref(self.__mirror), x, '#') 
				if test: 
					raise IOError("Error reading file: %s" % (x)) 
				else:
					pass 
			else: 
				raise IOError("File not found: %s" % (x)) 	 
		else: 
			# Failsafe 
			raise SystemError("Dataframe __init__ Error: 1") 





class __dataframe(Structure): 

	_fields_ = [
		("data", POINTER(POINTER(c_double))), 
		("num_rows", c_long), 
		("num_cols", c_int) 
	]


