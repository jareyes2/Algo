CC=g++
CFLAGS=
INC=
LIB=

all: buckets

buckets:  driver.o graph.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^ 

driver.cpp:  graph.hpp graph.cpp

clean:
	rm -f *.o buckets
