CC=g++
CFLAGS=--std=c++23 -O3

logs: logs.cpp
	$(CC) -o logs logs.cpp $(CFLAGS)
