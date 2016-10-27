CC=gcc
CFLAGS=-c -Wall -g

all: p1

p1: server.o p1.o
	$(CC) server.o p1.o -o p1

server.o: server.c
	$(CC) $(CFLAGS) server.c

p1.o: p1.c
	$(CC) $(CFLAGS) p1.c

clean:
	/bin/rm -f p1 *.o *.gz

run:
	./p1 8080

tarball:
	tar -cvzf p1sol.tar.gz *
