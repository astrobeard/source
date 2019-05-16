"""
Plot up the star formation efficiency as a function of time and the assoiated 
[O/Fe]-[Fe/H] tracks for up to 6 VICE outputs. 

ARGV:
=====
1)			The name of the output image 
2)			The name of the first integration 
3)			The name of the second integration 
4)			The name of the third integration 
5) 			The name of the fourth integration 
6)			The name of the fifth integration 
7)			The name of the sixth integration 
"""

import mplparams 
import matplotlib.pyplot as plt 
from ultra.visuals import colors 
import vice 
import sys 

_COLORS_ = ["black", "crimson", "lime", "blue", "purple", "gold"] 

def initialize_subplots(): 
	fig = plt.figure(figsize = (14, 7)) 
	ax1 = fig.add_subplot(121, facecolor = "white") 
	ax2 = fig.add_subplot(122, facecolor = "white") 
	ax1.set_xlabel("Time [Gyr]") 
	ax1.set_ylabel(r"$\tau_*$ [Gyr]") 
	ax2.set_xlabel("[Fe/H]") 
	ax2.set_ylabel("[O/Fe]") 
	return [ax1, ax2] 

def draw(axes, name, color): 
	hist = vice.history(name) 
	axes[0].plot(hist["time"], 
		map(lambda x, y: 1.e-9 * x / y, hist["mgas"], hist["sfr"]), 
		c = colors()[color]
	)
	axes[1].plot(hist["[Fe/H]"], hist["[O/Fe]"], c = colors()[color]) 

if __name__ == "__main__": 
	axes = initialize_subplots() 
	sims = sys.argv[2:]
	for i in range(len(sims)): 
		draw(axes, sims[i], _COLORS_[i]) 
	plt.tight_layout() 
	plt.savefig(sys.argv[1]) 
	plt.clf() 









