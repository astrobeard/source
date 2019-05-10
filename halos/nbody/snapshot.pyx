# cython: language_level=3, boundscheck=False 
"""
SNAPSHOT struct wrapping. 
"""

from ctypes import * 
from ..src cimport snapshot as src

class snapshot(object): 
	"""
	Attrbutes 
	========= 
	file :: str 
		The name of the file that the data originated from. 
	"""
	def __init__(self, filename, comment = '#'): 
		self.__snapshot = __SNAPSHOT() 
		src.populate_data_from_file(
			self.__snapshot, 
			c_char_p(filename), 
			c_char(comment)
		)


class __SNAPSHOT(Structure): 
	"""
	Wrapping of the SNAPSHOT struct defined in ../src/snapshot.h 
	"""
	_fields_ = [
		("data", POINTER(POINTER(c_double))), 
		("num_rows", c_long), 
		("num_cols", c_int)
	]




