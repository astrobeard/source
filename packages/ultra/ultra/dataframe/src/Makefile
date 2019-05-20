
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = dataframe_sieve.o dataframe_utils.o dataframe_sorting.o dataframe_io.o \
	dataframe_subs.o 

all: dataframe.so 

.PHONY: clean 

dataframe.so: $(OBJECTS) 
	$(CC) *.o -shared -o dataframe.so 

test.o: test.c dataframe.h dataframe_io.c dataframe_subs.c dataframe_utils.c 
	$(CC) test.c dataframe_io.c dataframe_subs.c dataframe_utils.c -o test.o 

%.o: %.c *.h
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 



