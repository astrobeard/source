
CC = gcc 
CFLAGS = -c -fPIC 
OBJECTS = snapshot_io.o snapshot_utils.o shapshot_subs.o 

all: snapshot.so 

.PHONY: clean 

snapshot.so: $(OBJECTS) 
	$(CC) *.o -shared -o snapshot.so 

# test.o: test.c snapshot.h snapshot_io.c 
# 	$(CC) test.c snapshot_io.c snapshot_utils.c -o test.o 

%.o: %.c *.h
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
	rm -f *.so 



