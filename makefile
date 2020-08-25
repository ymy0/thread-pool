CC = g++ -std=c++11 -lpthread.h

client:client.o
	$(CC) client.o -o client

server:service.o
	$(CC) service.o -o server

client.o:Client.cpp
	$(CC) -c Client.cpp

service.o:Service.cpp
	$(CC) -c Service.cpp

thread.o: Thread.cpp Thread.h
	$(CC) -c Thread.cpp

clean:
	rm -f *.o client server
