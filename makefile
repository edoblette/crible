CC=g++
CFLAGS= -Wall -std=c++17
LINK= -O3 -pthread

all:

	$(CC) $(LINK) $(CFLAGS) -o exo1 exo1.cpp
clear:
	rm exo1.o ./exo1


