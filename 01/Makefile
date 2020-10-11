CC = g++
FLAGS = -std=c++17

all: main

main: main.o MyAllocator.o
	$(CC) $(FLAGS) -o main main.o MyAllocator.o

test: test.o MyAllocator.o
	$(CC) $(FLAGS) -o test test.o MyAllocator.o

main.o: main.cpp MyAllocator.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp MyAllocator.h
	$(CC) $(FLAGS) -c test.cpp

MyAllocator.o: MyAllocator.cpp MyAllocator.h
	$(CC) $(FLAGS) -c MyAllocator.cpp

clean:
	rm -f *.o main test