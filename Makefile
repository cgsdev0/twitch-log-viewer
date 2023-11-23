CC=g++
CFLAGS=--std=c++23 -g

logs: logs.cpp
	$(CC) -o logs logs.cpp $(CFLAGS)
