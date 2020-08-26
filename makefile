CC = g++
DD = -std=c++11 -lpthread

all: Client.cpp Service.cpp Thread.o
	$(CC) Client.cpp -o client
	$(CC) Service.cpp Thread.o -o server $(DD)

Thread.o: Thread.cpp
	$(CC) -c Thread.cpp $(DD)

clean:
	rm -f *.o client server
