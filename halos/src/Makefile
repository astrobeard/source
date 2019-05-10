
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = snapshot_io.o 

all: snapshot.so test.o 

.PHONY: clean 

snapshot.so: $(OBJECTS) 
	$(CC) *.o -shared -o snapshot.so 

test.o: test.c snapshot.h snapshot_io.c 
	$(CC) test.c snapshot_io.c snapshot_utils.c -o test.o 

%.o: %.c 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 



