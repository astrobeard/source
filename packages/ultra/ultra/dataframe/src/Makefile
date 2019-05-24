
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = dataframe_sieve.o dataframe_utils.o dataframe_sorting.o \
	dataframe_io.o dataframe_subs.o 

all: dataframe.so 

.PHONY: clean 

dataframe.so: $(OBJECTS) 
	$(CC) *.o -shared -o dataframe.so 

test.o: utils.h dataframe.h *.c 
	$(CC) *.c -o test.o 

%.o: %.c *.h
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 



