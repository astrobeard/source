"""
ultra global variables 
====================== 
This module contains variables that are global to ultra 
"""

import os 

# The path to the directory after installation 
_DIRECTORY_ = "%s/" % (os.path.dirname(os.path.abspath(__file__))) 

def _VERSION_ERROR_(): 
	"""
	Raises a RuntimeError in the event that ultra is being imported into an 
	unsupported version of python. >= 3.5 is required. 
	"""
	raise RuntimeError("Python version >= 3.5 is required for ultra.") 

del os 
