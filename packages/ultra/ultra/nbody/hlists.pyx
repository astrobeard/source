# cython: language_level=3, boundscheck = False 
"""
This script contains source code for wrapping hlist tools implemented in C. 
"""

from .._globals import _DIRECTORY_ 
from .._globals import _VERSION_ERROR_ 
import numbers 
import sys 
import os 
if sys.version_info[:2] <= (3, 5): 
	raise RuntimeError("Python version >= 3.5 is required for ultra.") 
else:
	pass 

from ctypes import * 

"""
<--------------- C routine comment headers not duplicated here --------------->

Conventionally these would be declared in a .pxd file and imported, but this 
is simpler when there are only a few of them. 
"""
cdef extern from "src/hlists.h": 
	int condense(char *file, char *commenter, char *outfile, double minlogm, 
		int masscol) 

def resolution_filter(infilename, outfilename, comment = '#', 
	minlogm = 9.8, masscol = 10): 
	"""
	Condense an hlist halo catalog based on a minimum mass measurement. 

	Signature: ultra.nbody.hlists.resolution_filter(infilename, outfilename, 
		comment = '#', minlogm = 9.8, masscol = 10) 

	Parameters 
	========== 
	infilename :: str 
		The name of the hlist to condense 
	outfilename :: str 
		The name of the output condense hlist file 
	comment :: char [default :: '#'] 
		The commenting character at the beginning of each line of the header 
	minlogm :: real number [default :: 9.8] 
		The minimum logarithmic halo mass 
	masscol :: int [default :: 10] 
		The column number of halo masses to filter based on 
	""" 

	# Type checking errors 
	if not isinstance(infilename, str): 
		raise TypeError("First argument must be of type str. Got: %s" % (
			type(infilename))) 
	elif not isinstance(outfilename, str): 
		raise TypeError("Second argument must be of type str. Got: %s" % (
			type(outfilename))) 
	elif not isinstance(comment, str): 
		raise TypeError("Keyword argument 'comment' must be of type str. Got: \
%s" % (type(comment))) 
	elif not isinstance(minlogm, numbers.Number): 
		raise TypeError("Keyword argument 'minlogm' must be a real number. Got: \
%s" % (type(minlogm))) 
	elif not isinstance(masscol, numbers.Number) and masscol % 1 != 0: 
		raise TypeError("Keyword argument 'masscol' must be of type int. Got: \
%s" % (type(masscol))) 
	else: 
		pass 

	if not os.path.exists(infilename): 
		raise IOError("File does not exist: %s" % (infilename)) 
	else:
		pass 

	cdef int x = condense(
		infilename.encode("latin-1"), 
		comment.encode("latin-1"), 
		outfilename.encode("latin-1"), 
		minlogm, 
		masscol) 

	if x == 1: 
		raise IOError("Error on reading input file: %s" % (infilename)) 
	elif x == 2: 
		raise IOError("Error on writing output file: %s" % (outfilename)) 
	elif x == 0: 
		pass 
	else: 
		raise SystemError("Unknown return parameter: %d" % (x)) 






