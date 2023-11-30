CC=g++
CFLAGS=--std=c++23

logs: logs.cpp
	$(CC) -o logs logs.cpp $(CFLAGS)
