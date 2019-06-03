
__all__ = ["xticklabel_formatter", "yticklabel_formatter", "colors", 
	"mpl_loc", "markers", "append_subplot_below"]  

import matplotlib as mpl 
import matplotlib.pyplot as plt 
from matplotlib.ticker import FormatStrFormatter as _fsf 
from mpl_toolkits.axes_grid1 import make_axes_locatable 
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes as zia 
import numbers 

def append_subplot_below(subplot, scale, **kwargs): 
	"""
	Puts a new subplot on the bottom of the one passed as an argument. 

	Parameters 
	========== 
	subplot :: pyplot subplot 
		Any instance of a subplot from matplotlib 
	scale :: real number > 0 
		A number describing the size of the appended subplot relative to the 
		root one passed to this function 
	kwargs :: varying types 
		Other keyword arguments to pass to 
		mpl_toolkits.axes_grid1.make_axes_locatable 

	Returns 
	======= 
	The new subplot instance 

	Raises 
	====== 
	TypeError :: 
		:: subplot is not a matplotlib subplot instance 
		:: scale is not a real number 
	ValueError :: 
		:: scale is less than or equal to zero 
	Other exceptions will be raised from within matplotlib regarding keyword 
	arguments 
	""" 
	if isinstance(subplot, mpl.axes._subplots.Axes): 
		if isinstance(scale, numbers.Number): 
			if scale > 0: 
				return make_axes_locatable(subplot).append_axes("bottom", 
					scale, 
					**kwargs) 
			else: 
				raise ValueError("Second argument must be > 0. Got: %g" % (
					scale)) 
		else: 
			raise TypeError("Second argument must be a real number. Got: %s" % (
				type(scale))) 
	else: 
		raise TypeError("First argument must be a matplotlib subplot. Got: %s" % (
			type(subplots))) 

def xticklabel_formatter(subplot, fmt = "%g"):
	"""
	Format existing x-axis ticklabels according to the formatting string.

	Parameters 
	========== 
	subplot :: matplotlib subplot 
		The subplot to format the x-axis tick labels for 

	Kwargs:
	=======
	fmt :: str 
		A formatting string that will be passed to 
		matplotlib.ticker.FormatStrFormatter
	"""
	# Get the major and minor tick labels and determine visibility
	subplot.figure.canvas.draw()
	majorlabels = [i.get_text() for i in subplot.xaxis.get_majorticklabels()]
	minorlabels = [i.get_text() for i in subplot.xaxis.get_minorticklabels()]
	majorvisible = map(lambda x: x != "", majorlabels)
	minorvisible = map(lambda x: x != "", minorlabels)
	# Set the major and minor formatter according to the format
	subplot.xaxis.set_major_formatter(_fsf(fmt))
	subplot.xaxis.set_minor_formatter(_fsf(fmt))
	subplot.figure.canvas.draw()
	# Change the labels of originally invisible labels to ""
	new_majorlabels = [i.get_text() for i in 
		subplot.xaxis.get_majorticklabels()]
	new_minorlabels = [i.get_text() for i in 
		subplot.xaxis.get_minorticklabels()]
	for i in range(len(majorvisible)):
		if majorvisible[i]:
			pass
		else:
			new_majorlabels[i] = ""
	for i in range(len(minorvisible)):
		if minorvisible[i]:
			pass
		else:
			new_minorlabels[i] = ""
	subplot.set_xticklabels(new_majorlabels, minor = False)
	subplot.set_xticklabels(new_minorlabels, minor = True)

def yticklabel_formatter(subplot, fmt = "%g"):
	"""
	Format existing y-axis ticklabels according to the formatting string.

	Parameters 
	========== 
	subplot :: matplotlib subplot 
		The subplot to format the y-axis tick labels for 

	Kwargs:
	=======
	fmt :: str 
		A formatting string that will be passed to 
		matplotlib.ticker.FormatStrFormatter
	"""
	# Get the major and minor tick labels and determine visibility
	subplot.figure.canvas.draw()
	majorlabels = [i.get_text() for i in subplot.yaxis.get_majorticklabels()]
	minorlabels = [i.get_text() for i in subplot.yaxis.get_minorticklabels()]
	majorvisible = map(lambda x: x != "", majorlabels)
	minorvisible = map(lambda x: x != "", minorlabels)
	# Set the major and minor formatter according to the format
	subplot.yaxis.set_major_formatter(_fsf(fmt))
	subplot.yaxis.set_minor_formatter(_fsf(fmt))
	subplot.figure.canvas.draw()
	# change the labels of originally invisible labels to ""
	new_majorlabels = [i.get_text() for i in 
		subplot.yaxis.get_majorticklabels()]
	new_minorlabels = [i.get_text() for i in 
		subplot.yaxis.get_minorticklabels()]
	for i in range(len(majorvisible)):
		if majorvisible[i]:
			pass
		else:
			new_majorlabels[i] = ""
	for i in range(len(minorvisible)):
		if minorvisible[i]:
			pass
		else:
			new_minorlabels[i] = ""
	subplot.set_yticklabels(new_majorlabels, minor = False)
	subplot.set_yticklabels(new_minorlabels, minor = True) 

def colors():

	"""
	Returns 
	======= 
	A dictionary of color names to matplotlib colors
	"""
	return mpl.colors.get_named_colors_mapping() 

def mpl_loc(label):
	"""
	Parameters 
	========== 
	label :: str 
		A string. A descriptive location of a point in a box.
			Recognized inputs:
				'best'
				'upper right'
				'upper left'
				'lower left'
				'lower right'
				'right'
				'center left'
				'center right'
				'lower center'
				'upper center'
				'center'

	Returns the matplotlib integer denoting the location within the box
	"""
	indeces = {"best": 0,
		"upper right": 1,
		"upper left": 2,
		"lower left": 3,
		"lower right": 4,
		"right": 5,
		"center left": 6,
		"center right": 7,
		"lower center": 8,
		"upper center": 9,
		"center": 10}

	try:
		return indeces[label.lower()]
	except:
		raise ValueError("Unrecognized location string: %s" % (label))

def markers():
	"""
	Returns a dictionary of terms to matplotlib marker characters.

	Recognized markers
	================== 
	point
	pixel
	circle
	triangle_down
	triangle_up
	triangle_left
	triangle_right
	tri_down
	tri_up
	tri_left
	tri_right
	octagon
	square
	pentagon
	plus_filled
	star
	hexagon1
	hexagon2
	plus
	x
	x_filled
	diamond
	thin_diamond
	vline
	hline
	tickleft
	tickright
	tickup
	tickdown
	caretright
	caretleft
	caretup
	caretdown
	caretrightbase
	caretleftbase
	caretupbase

	Example:
	This line of code will produce the scatter plot in red stars:
	plt.plot(range(10), range(10, 20), '%c%c' % (
		graphics.colors()['red'], 
		graphics.markers()['star']
	))
	"""
	return {"point":		".", 
		"pixel":			",", 
		"circle":			"o",
		"triangle_down":	"v",
		"circle":			"o",
		"triangle_down":	"V",
		"triangle_up":		"^", 
		"triangle_left":	"<", 
		"triangle_right":	">",
		"tri_down":			"1",
		"tri_up":			"2", 
		"tri_left":			"3", 
		"tri_right":		"4", 
		"octagon":			"8", 
		"square": 			"s", 
		"pentagon":			"p", 
		"plus_filled":		"P", 
		"star":				"*",
		"hexagon1":			"h", 
		"hexagon2":			"H", 
		"plus":				"+",
		"x":				"x", 
		"x_filled":			"X", 
		"diamond":			"D", 
		"thin_diamond":		"d", 
		"vline":			"|", 
		"hline":			"_", 
		"tickleft":			"TICKLEFT",
		"tickright":		"TICKRIGHT",
		"tickup":			"TICKUP",
		"tickdown":			"TICKDOWN", 
		"caretright":		"CARETRIGHT", 
		"caretleft":		"CARETLEFT", 
		"caretup":			"CARETUP",
		"caretdown":		"CARETDOWN",
		"caretrightbase":	"CARETRIGHTBASE", 
		"caretleftbase":	"CARETLEFTBASE",
		"caretupbase":		"CARETUPBASE"
	}



