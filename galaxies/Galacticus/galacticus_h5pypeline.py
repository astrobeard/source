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
	return ("z%.2f" % (z)).replace('.', 'p') 

def write_phase_space(indata, outdata): 
	""" 
	Writes phase space information from indata to outdata, both h5py file 
	objects 

	example of where this is found in raw Galacticus output: 
		indata["Outputs/Output1/nodeData/satellitePositionX"] 
	""" 
	phase_space = tuple(["satellitePositionX", "satellitePositionY", 
		"satellitePositionZ", "satelliteVelocityX", "satelliteVelocityY", 
		"satelliteVelocityZ"]) 
	for i in range(len(_OUTPUT_Z_)): 
		for j in phase_space: 
			key = "Outputs/Output%d/nodeData/%s" % (i + 1, j) 
			outdata["%s/%s" % (get_z_string(_OUTPUT_Z_[i]), j)] = indata[key][:] 

def write_mass(indata, outdata): 
	""" 
	Writes the satellite masses to the output file 

	example of where this is found in raw Galacticus output: 
		indata["Outputs/Output1/nodeData/basicMass"] 
	""" 
	for i in range(len(_OUTPUT_Z_)): 
		key = "Outputs/Output%d/nodeData/basicMass" % (i + 1) 
		outdata["%s/satelliteMass" % (
			get_z_string(_OUTPUT_Z_[i]))] = indata[key][:] 

def write_concentration(indata, outdata): 
	""" 
	Writes the satellite concentration to the output file 

	c = Rvir/Rscale 

	Rvir and Rscale stored at "Outputs/OutputX/nodeData/nodeVirialRadius" and 
	"Outputs/OutputX/nodeData/darkMatterProfileScale" in raw Galacticus output 
	""" 
	for i in range(len(_OUTPUT_Z_)): 
		stem = "Outputs/Output%d/nodeData" % (i + 1) 
		outdata["%s/satelliteConcentration" % (
			get_z_string(_OUTPUT_Z_[i]))] = np.array(
				list(map(lambda x, y: x / y, 
					indata["%s/nodeVirialRadius" % (stem)][:], 
					indata["%s/darkMatterProfileScale" % (stem)][:])) 
			) 

def write_IDs(indata, outdata): 
	"""
	Writes satellite IDs to the output file. The IDs are strings of the format: 

	mergerTreeIndex.nodeIndex 

	These are both subgroups stored at "Outputs/OutputX/nodeData" in raw 
	Galacticus outputs 
	""" 
	for i in range(len(_OUTPUT_Z_)): 
		stem = "Outputs/Output%d/nodeData" % (i + 1) 
		IDs = len(indata["%s/nodeIndex" % (stem)]) * [None] 
		for j in range(len(IDs)): 
			IDs[j] = "%d.%d" % (
				indata["%s/mergerTreeIndex"][j], 
				indata["%s/nodeIndex"][j]
			) 
		outdata["%s/satelliteID" % (get_z_string(_OUTPUT_Z_[i]))] = np.array(IDs)  


if __name__ == "__main__": 
	# open the Galacticus output and the condensed hdf5 output file
	indata = h5py.File(sys.argv[1], 'r')  
	with h5py.File(sys.argv[2], 'w') as outdata: 
		write_phase_space(indata, outdata) 
		write_mass(indata, outdata) 
		write_concentration(indata, outdata) 



