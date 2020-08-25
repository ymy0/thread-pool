CC = g++ -std=c++11 -lpthread.h

thread.o: Thread.cpp Thread.h
	$(CC) -c Thread.cpp


