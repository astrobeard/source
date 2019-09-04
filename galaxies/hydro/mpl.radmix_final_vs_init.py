"""
The following produces a plot of final orbital radius versus initial orbital 
radius from the UW hydro simulation. 
"""

import mplparams 
import matplotlib.pyplot as plt 
from vice import dataframe 
from ultra.io import read 
from ultra.arrays import scatter 
from ultra.arrays import error_from_mean
import ultra.visuals as v
import numpy as np 
import sys
import os 

tformcol = 1
rformcol = 2
rfinalcol = 4 

def read_data(filename = "%shydro/particle_track_radmix_initial.dat" % (
	os.environ["DATA_DIRECTORY"])): 
	data = read(filename) 
	frame = {} 
	frame["tform"] = [i[tformcol] for i in data]
	frame["rform"] = [i[rformcol] for i in data] 
	frame["rfinal"] = [i[rfinalcol] for i in data]
	return dataframe(frame) 

def initialize_subplot(): 
	fig = plt.figure(figsize = (7, 7)) 
	ax = fig.add_subplot(111, facecolor = "white") 
	ax.set_xlabel(r"$R_\text{form}$ [kpc]") 
	ax.set_ylabel(r"$R_\text{final}$ [kpc]") 
	ax.set_xlim([-2, 17]) 
	ax.set_ylim([-2, 17])
	return ax 

def analyze(data, rformbins, tformbin): 
	indeces = filter(lambda x: tformbin[0] <= data[x]["tform"] <= tformbin[1], 
		range(len(data["tform"]))) 
	raw = [data[i] for i in indeces]
	binned = (len(rformbins) - 1) * [None]
	for i in range(len(binned)): 
		binned[i] = filter(lambda x: rformbins[i] <= x["rform"] <= 
			rformbins[i + 1], raw) 
	y = len(binned) * [0] 
	err = len(binned) * [0] 
	scat = len(binned) * [0] 
	x = map(lambda x, y: (x + y) / 2., rformbins[:-1], rformbins[1:]) 
	for i in range(len(binned)): 
		try:
			y[i] = np.mean([j["rfinal"] for j in binned[i]]) 
			err[i] = error_from_mean([j["rfinal"] for j in binned[i]]) 
			scat[i] = scatter([j["rfinal"] for j in binned[i]]) 
		except: 
			y[i] = 0
			err[i] = 0
			scat[i] = [0, 0]
	return [x, y, err, scat]

def draw(ax, x, y, err, scat, color): 
	ax.plot(x, y, c = v.colors()[color]) 
	# ax.fill_between(x, map(lambda y1, y2: y1 - y2, y, err), 
	# 	map(lambda y1, y2: y1 + y2, y, err), 
	# 	color = v.colors()[color], alpha = 0.3) 
	ax.plot(x, [i[0] for i in scat], c = v.colors()[color], linestyle = ':') 
	ax.plot(x, [i[1] for i in scat], c = v.colors()[color], linestyle = ':') 

def one_to_one_line(ax): 
	xlim = ax.get_xlim()
	ax.plot(xlim, xlim, c = v.colors()["black"], linestyle = '--') 
	ax.set_xlim(xlim) 

def legend(ax, tformbins, colors): 
	# labels = (len(tformbins) - 1) * [None]
	labels = len(tformbins) * [None] 
	lines = len(labels) * [None]
	for i in range(len(labels)): 
		# labels[i] = r"$%g\text{ Gyr}\leq T_\text{form}\leq %g\text{ Gyr}$" % (
		# 	tformbins[i], tformbins[i + 1]) 
		# labels[i] = r"$T_\text{form}\in[%g;%g]$ Gyr" % (tformbins[i], 
		# 	tformbins[i + 1])
		labels[i] = r"$T_\text{form}\in[%g;%g]$ Gyr" % (tformbins[i][0], 
			tformbins[i][1])
		lines[i] = ax.plot([1, 2], [1, 2], c = v.colors()["white"], 
			label = labels[i])[0] 
	leg = ax.legend(loc = v.mpl_loc("upper left"), ncol = 1, frameon = False, 
		bbox_to_anchor = (-0.02, 0.98), handlelength = 0) 
	for i in range(len(lines)): 
		lines[i].remove() 
		leg.get_texts()[i].set_color(colors[i])

if __name__ == "__main__": 
	data = read_data() 
	ax = initialize_subplot()
	# tformbins = [[3, 6], [6, 9], [9, 12]]
	tformbins = [[0, 2], [2, 4], [4, 6], [6, 8], [8, 10], [10, 12]] 
	rformbins = np.linspace(0, 15, 51)
	colors = ["black", "crimson", "lime", "blue", "purple"] 
	# for i in range(len(tformbins) - 1): 
	for i in range(len(tformbins)): 
		x, y, err, scat = analyze(data, rformbins, 
			# [tformbins[i], tformbins[i + 1]])
			tformbins[i]) 
		draw(ax, x, y, err, scat, colors[i])
	one_to_one_line(ax)
	legend(ax, tformbins, colors)
	ax.yaxis.set_ticks([0, 5, 10, 15]) 
	plt.tight_layout()
	plt.savefig("%sgalaxies/hydro/finalvform.pdf" % (
		os.environ["PLOTS_DIRECTORY"]))
	plt.clf() 





