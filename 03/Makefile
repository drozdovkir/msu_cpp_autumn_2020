CC = g++
FLAGS = -std=c++17

all: main

main: main.out
	./main.out

main.out: main.o Matrix.o
	$(CC) $(FLAGS) -o main.out main.o Matrix.o

test: test.out
	./test.out

test.out: test.o Matrix.o
	$(CC) $(FLAGS) -o test.out test.o Matrix.o

main.o: main.cpp Matrix.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp Matrix.h
	$(CC) $(FLAGS) -c test.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(FLAGS) -c Matrix.cpp

clean:
	rm -f *.o main.out test.out