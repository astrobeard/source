
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = hlists_massfilter.o  

all: hlists.so 

.PHONY: clean 

hlists.so: $(OBJECTS)  
	$(CC) *.o -shared -o hlists.so 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 


