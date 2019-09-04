""" 
Run the replication of the UW hydrodynamic simulation with VICE's multizone 
features 
""" 

import matplotlib.pyplot as plt 
from ultra.visuals import make_matplotlib_pretty_again 
import ultra.visuals as v 
import pickle 
import numpy as np 
import math as m 
import vice 
import sys 
import os 

print("Reading in data....") 
datapath = "%shydro/particle_track_radmix_initial.dat" % (
	os.environ["DATA_DIRECTORY"]) 
data = np.genfromtxt(datapath).tolist() 
tform = [row[1] for row in data] 
Rform = [row[2] for row in data] 
tfinal = len(data) * [13.8] 
Rfinal = [row[4] for row in data] 
data = [list(i) for i in zip(tform, tfinal, Rform, Rfinal, len(tform) * [0], 
	len(tform) * [0], len(tform) * [0])]  
# data[0]: tform 
# data[1]: tfinal 
# data[2]: rform 
# data[3]: rfinal 
# data[4]: formation zone 
# data[5]: formation time bin 
# data[6]: final zone 

def get_bin_number(bins, val): 
	# print(val) 
	for i in range(len(bins) - 1): 
		if bins[i] <= val <= bins[i + 1]: return i
	return -1

time_bins = np.linspace(0, 13.8, 21) 
rad_bins = np.linspace(0, 30, 31) 

print("Tracking....") 
for i in range(len(data)): 
	data[i][-3] = get_bin_number(rad_bins, data[i][2]) 
	data[i][-2] = get_bin_number(time_bins, data[i][0]) 
	data[i][-1] = get_bin_number(rad_bins, data[i][3]) 
	sys.stdout.write("Progress: %.2f%%\r" % (100 * (i + 1) / len(data))) 
	sys.stdout.flush() 
sys.stdout.write("\n") 

migration = len(rad_bins) * [None] 
for i in range(len(migration)): 
	migration[i] = len(time_bins) * [None] 
	for j in range(len(migration[i])): 
		migration[i][j] = len(rad_bins) * [0] 

print("Producing migration data....") 
for i in range(len(data)): 
	migration[data[i][4]][data[i][5]][data[i][6]] += 1
	sys.stdout.write("Progress: %.2f%%\r" % (100 * (i + 1) / len(data))) 
	sys.stdout.flush() 
sys.stdout.write("\n") 

for i in range(len(migration)): 
	for j in range(len(migration[i])): 
		if sum(migration[i][j]) == 0: migration[i][j][i] = 1 

def tracer_settings(orig, t): 
	tbin = get_bin_number(time_bins, t)
	def dist(final): 
		return migration[int(orig)][tbin][int(final)] 
	return dist 

print("Setting up multizone simulation....") 
from vice.yields.presets import my_yields
mz = vice.multizone(name = "diskmodel", n_zones = len(rad_bins) - 1, 
	n_tracers = 10, verbose = True)  
def get_ifr(tau): 
    def ifr(t): 
        return 6.0 / (tau * (1 - m.exp(-13.8 / tau))) * m.exp(-t / tau) 
    return ifr 
for i in range(mz.n_zones): 
    mz.zones[i].bins = np.linspace(-3, 1, 401) 
    mz.zones[i].elements = ["mg", "fe", "o"] 
mz.migration.stars = tracer_settings 
print("Running....") 
mz.run(np.linspace(0, 13.8, 1381)) 

