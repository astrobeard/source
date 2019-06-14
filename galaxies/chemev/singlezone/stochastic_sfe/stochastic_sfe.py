"""
Run a VICE model with a stochastic star formation efficiency. Infall rate is 
otherwise constant at 9.1 Msun yr^-1. 

ARGV:
=====
1)		The name of the simulation 
2) 		The mean star formation efficiency 
3) 		The standard deviation of the white noise in SFE 
4) 		(optional) -f to force overwrite 
"""

import numpy as np 
import vice 
import sys 

def tau_star(t):
	"""
	The star formation efficiency as a function of time with white noise 
	simulated according to user-specified standard deviation. 
	""" 
	test = float(sys.argv[2]) + np.random.normal(
		scale = float(sys.argv[3]))

	while test < 0: 
		# Don't allow negative star formation efficiencies 
		test = float(sys.argv[2]) + np.random.normal(
			scale = float(sys.argv[3]))

	return test 

def get_integrator(): 
	"""
	Get an instance of VICE's singlezone integrator. 
	"""
	sz = vice.singlezone(name = sys.argv[1]) 
	sz.tau_star = tau_star 
	return sz 

if __name__ == "__main__": 
	if "-f" in sys.argv: 
		force = True 
	else:
		force = False 

	get_integrator().run(np.linspace(0, 10, 1001), overwrite = force)

