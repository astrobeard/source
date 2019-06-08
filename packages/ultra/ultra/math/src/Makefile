
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = trigonometry.o utils.o 

all: ultramath.so 

.PHONY: clean 

ultramath.so: $(OBJECTS) 
	$(CC) *.o -shared -o ultramath.so 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 

