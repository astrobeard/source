
CC = gcc 
CFLAGS = -c -fPIC 
PYDIR = /Library/Frameworks/Python.framework/Versions/3.7/Headers 
OBJECTS = trigonometry.o utils.o 

all: ultramath.so 

.PHONY: clean 

ultramath.so: $(OBJECTS) 
	$(CC) *.o -shared -o ultramath.so 

%.o: %.c *.h 
	$(CC) $(CFLAGS) -I$(PYDIR) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 

