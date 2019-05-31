
CC = gcc 
CFLAGS = -c -fPIC 
all: hlist_massfilter.o 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 


