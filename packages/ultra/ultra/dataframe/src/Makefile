
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = dataframe_sieve.o dataframe_utils.o dataframe_sorting.o 

all: dataframe.so 

.PHONY: clean 

dataframe.so: $(OBJECTS) 
	$(CC) *.o -shared -o dataframe.so 

# test.o: test.c snapshot.h snapshot_io.c 
# 	$(CC) test.c snapshot_io.c snapshot_utils.c -o test.o 

%.o: %.c *.h
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 



