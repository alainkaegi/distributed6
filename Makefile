CFLAGS = -Wall -O3 -g3

all: server6 client6

getaddrinfo6.o: getaddrinfo6.c getaddrinfo6.h
server6.o: server6.c getaddrinfo6.h
client6.o: client6.c getaddrinfo6.h

server6: server6.o getaddrinfo6.o
	$(CC) server6.o getaddrinfo6.o -o server6 -lrt

client6: client6.o getaddrinfo6.o
	$(CC) client6.o getaddrinfo6.o -o client6

clean:
	@rm -f server6 client6 server6.o client6.o getaddrinfo6.o
