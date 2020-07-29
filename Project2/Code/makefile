cc=gcc
CFLAGS=-std=c99

run: driver.o sums.o fileReader.o
	g++ -o run driver.o sums.o fileReader.o
driver.o: driver.cpp sums.h
	g++ -c driver.cpp 
sums.o: sums.cpp sums.h
	g++ -c sums.cpp
fileReader.o: fileReader.cpp fileReader.h
	g++ -c fileReader.cpp





