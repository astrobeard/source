"""
The following is a script which condenses Galacticus outputs to satellite masses, 
orbital position and velocity of satellites, gravitaional potential, and dwarf 
structural parameters at each output timestep. 

ARGV:
=====
1)		The name of the intput hdf5 file
2) 		The name of the output hdf5 file 
"""

import h5py 
import sys 

if __name__ == "__main__": 
	indata = h5py.File(sys.argv[1], 'r')["Outputs/Output1/nodeData"]
	with h5py.File(sys.argv[2], 'w') as outdata: 
		keys = tuple(["satellitePositionX" "satellitePositionY", 
			"satellitePositionZ", "satelliteVelocityX", "satelliteVelocityY", 
			"satelliteVelocityZ"])
		
		for i in keys: 
			outdata[i] = indata[i][:]




