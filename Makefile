CC = gcc
CFLAGS = --std=c2x -Wall -Werror -pedantic
OBJECTS = main.o priority_queue.o
PROGRAM = main
HEADERS = priority_queue.h

all: main
main: main.o priority_queue.o
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(HEADERS)
clean:
	rm $(PROGRAM) *.o *.gch