
_MIN_CYTHON_MAJOR_ = 0 
_MIN_CYTHON_MINOR_ = 25 
_MIN_CYTHON_MICRO_ = 2 

try: 
	ModuleNotFoundError 
except NameError: 
	ModuleNotFoundError = ImportError 
try: 
	import Cython 
	from Cython.Build import cythonize 
except (ImportError, ModuleNotFoundError): 
	raise RuntimeError("""\
Please install Cython >= %d.%d.%d before installing ultra \
""" % (_MIN_CYTHON_MAJOR_, _MIN_CYTHON_MINOR_, _MIN_CYTHON_MICRO_)) 
if tuple([int(i) for i in Cython.__version__.split('.')]) < tuple([
	_MIN_CYTHON_MAJOR_, _MIN_CYTHON_MINOR_, _MIN_CYTHON_MICRO_]): 
	raise RuntimeError("""\
Building ultra requires Cython >= %d.%d.%d. Current version: %s\
""" % (_MIN_CYTHON_MAJOR_, _MIN_CYTHON_MINOR_, _MIN_CYTHON_MICRO_, 
	Cython.__version__))
else: 
	pass 

from distutils.core import setup, Extension 
import sys 
import os 

if sys.version_info[:2] < (3, 5): 
	raise RuntimeError("ultra requires python version >= 3.5.") 
else:
	pass 

package_name = "ultra" 
base_url = "http://github.com/giganano/ultra" 

import builtins 
builtins.__ULTRA_SETUP__ = True 
import ultra 

CLASSIFIERS = """\
Development Status :: 4 - Beta 
Intended Audience :: Developers 
Intended Audience :: Science/Research 
License :: OSI Approved :: MIT License 
Natural Language :: English 
Operating System :: POSIX 
Operating System :: Mac OS 
Operating System :: Mac OS :: Mac OS X 
Operating System :: Unix 
Programming Language :: C 
Programming Language :: Python :: 3 
Programming Language :: Python :: 3.5 
Programming Language :: Python :: 3.6 
Programming Language :: Python :: 3.7 
Programming Language :: Python :: Implementation :: CPython 
Topic :: Scientific/Engineering 
Topic :: Scientific/Engineering :: Astronomy 
Topic :: Scientific/Engineering :: Physics 
""" 

MAJOR 			= 0 
MINOR 			= 0 
MICRO 			= 0 
ISRELEASED		= False 
VERSION 		= "%d.%d.%d" % (MAJOR, MINOR, MICRO) 

def compile_extensions(): 
	"""
	Compiles each Cython extension 
	""" 
	for root, dirs, files in os.walk('.'): 
		for i in files: 
			# If this is Cython code 
			if i[-4:] == ".pyx": 
				c_extensions = list(filter(lambda x: x[-2:] == ".c", 
					["%s/src/%s" % (root, i) for i in os.listdir(
						"%s/src/" % (root))]
				)) 
				ext = "%s.%s" % (root[2:].replace('/', '.'), i.split('.')[0]) 
				files = ["%s/%s" % (root[2:], i)] + c_extensions 
				setup(ext_modules = cythonize([Extension(ext, files)])) 
			else:
				continue 
		

def find_packages(path = '.'): 
	"""
	Finds each subpackages given the presence of an __init__.py file 

	path: The relative path to the directory 
	""" 
	packages = [] 
	for root, dirs, files in os.walk(path): 
		if "__init__.py" in files: 
			packages.append(root[2:].replace('/', '.')) 
		else:
			continue 
	return packages 

def find_package_data(): 
	"""
	Finds data files associated with each package 
	""" 
	packages = find_packages() 
	data = {} 
	for i in packages: 
		if any(map(lambda x: x.split('.')[-1] in ["so"], 
			os.listdir(i.replace('.', '/')))): 
			data[i] = ["*.so"] 
		else: 
			continue 
	return data 

def write_version_info(filename = "ultra/version.py"): 
	""" 
	Writes the version info the filename 
	""" 
	cnt = """\
# This file is generated from ultra setup.py 

version = "%(version)s" 
release = %(isreleased)s 
""" 
	with open(filename, 'w') as f: 
		try: 
			f.write(cnt % {
					"version":		VERSION, 
					"isreleased": 	str(ISRELEASED) 
				})
		finally: 
			f.close() 

def setup_package(): 
	src_path = os.path.dirname(os.path.abspath(sys.argv[0])) 
	old_path = os.getcwd() 
	os.chdir(src_path) 
	sys.path.insert(0, src_path) 

	compile_extensions() 

	metadata = dict(
		name = package_name, 
		version = VERSION, 
		author = "James W. Johnson", 
		author_email = "giganano9@gmail.com", 
		maintainer = "James W. Johnson", 
		maintainer_email = "giganano9@gmail.com", 
		url = base_url, 
		description = "Generic Data Analysis in C", 
		long_description = ultra._LONG_DESCRIPTION_, 
		classifiers = CLASSIFIERS, 
		license = "MIT", 
		platforms = ["Linux", "Mac OS X", "Unix"], 
		keywords = ["data", "analysis", "numerical"], 
		provides = [package_name], 
		packages = find_packages(), 
		package_data = find_package_data() 
	) 

	try: 
		write_version_info() 
		setup(**metadata) 
	finally: 
		del sys.path[0] 
		os.system("rm -f ultra/version.py") 
		os.chdir(old_path) 
		return 

if __name__ == "__main__": 
	setup_package() 
	del builtins.__ULTRA_SETUP__ 


