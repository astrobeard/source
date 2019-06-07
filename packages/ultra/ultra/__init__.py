"""
ultra: generic data analysis in C 
"""

__author__ = "James W. Johnson <giganano9@gmail.com>" 

try: 
	ModuleNotFoundError 
except NameError: 
	ModuleNotFoundError = ImportError 
try: 
	__ULTRA_SETUP__ 
except NameError: 
	__ULTRA_SETUP__ = False 

if __ULTRA_SETUP__: 
	_LONG_DESCRIPTION_ = __doc__ 
else: 

	try: 
		from .version import version as __version__ 
	except (ImportError, ModuleNotFoundError): 
		raise ImportError("""\
Error importing ultra. ultra is a pre-compiled package and cannot be ran from \
its source directory, because the compiled objects are not stored here. Please \
exit the ultra source tree and relaunch your python interpreter from there. \
""") 

	__all__ = ["__author__", "__version__", "dataframe", "nbody"]  

	from .dataframe import * 
	from . import nbody 

	del version 



