
__all__ = ["make_matplotlib_pretty_again"] 

from .mplsubs import *
from . import make_matplotlib_pretty_again

__all__.extend(mplsubs.__all__) 
del mplsubs 
