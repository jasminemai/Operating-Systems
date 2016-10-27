CC=gcc
CFLAGS=-c -Wall -g

all: ex4

ex4: ex4.o
	$(CC) ex4.o -o ex4

ex4.o: ex4.c
	$(CC) $(CFLAGS) ex4.c 

clean:
	rm ex4
	rm ex4.o

run:
	./ex4

rundebug:
	gdb ex4
