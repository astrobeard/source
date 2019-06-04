"""
The following is a script which condenses Galacticus outputs to satellite masses, 
orbital position and velocity of satellites, gravitaional potential, and dwarf 
structural parameters at each output timestep. 

ARGV:
=====
1)		The name of the intput hdf5 file 
2) 		The name of the output hdf5 file 
"""

import numpy as np 
import h5py 
import sys 

_OUTPUT_Z_ = np.linspace(0, 1, 101).tolist() 

def get_z_string(z): 
	"""
	Get the redshift as a string of the format zXpXX representing z = X.XX 

	Example 
	======= 
	z = 0.27 -> 'z0p27' 
	"""
	return "z%dp%.2f" % (int(z), z % 1)  

if __name__ == "__main__": 
	# open the Galacticus output and the condensed hdf5 output file
	indata = h5py.File(sys.argv[1], 'r')  
	with h5py.File(sys.argv[2], 'w') as outdata: 
		# for each output redshift 
		for i in range(len(_OUTPUT_Z_)): 
			# Store the redshift in a z0p00 format where p represents the decimal 
			z_str = get_z_string(_OUTPUT_Z_[i]) 
			# Satellite phase space info 
			phase_space = tuple(["satellitePositionX", "satellitePositionY", 
				"satellitePositionZ", "satelliteVelocityX", "satelliteVelocityY", 
				"satelliteVelocityZ"]) 
			for j in phase_space: 
				"""
				Store this phase space coordinate at this output time 

				example of where this is found in raw Galacticus output: 
					indata["Outputs/Output1/nodeData/satellitePositionX"]
				"""
				indata_key = "Outputs/Output%d/nodeData/%s" % (i, j) 
				print(indata_key)
				outdata["%s/%s" % (z_str, j)] = indata[indata_key][:]

			"""
			Dwarf Structural Parameters 
			=========================== 
			Concentration :: 
				Rvir / Rscale 
				Write this at each output timestep to the output file 
			""" 
			# The concentration 
			outdata["%s/satelliteConcentration" % (z_str)] = np.array(
				map(lambda x, y: x / y, 
					indata["Outputs/Output%d/nodeData/nodeVirialRadius" % (i)][:], 
					indata["Outputs/Output%d/nodeData/darkMatterProfileScale" % (i)][:]
					))



