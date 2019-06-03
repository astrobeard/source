
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = hlists_massfilter.o hlists_io.o hlists_utils.o 

all: hlists.so 

.PHONY: clean 

hlists.so: $(OBJECTS)  
	$(CC) *.o -shared -o hlists.so 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 


