CC = g++
CFLAGS = -c -Wall

all: ./AKINATOR/akinator.cpp ./Stack/stack.cpp
	$(CC) $(CFLAGS) ./AKINATOR/v2.cpp -o akinator.o 
	$(CC) $(CFLAGS)	./Stack/stack.cpp -o stack.o
	$(CC) akinator.o stack.o -o akinator
	rm -rf *.o

clean:
	rm -rf akinator