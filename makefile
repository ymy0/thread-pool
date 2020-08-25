CC = g++ -std=c++11

thread.o: Thread.cpp Thread.h
	$(CC) -c Thread.cpp


