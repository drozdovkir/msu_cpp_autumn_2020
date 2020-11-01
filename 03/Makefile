CC = g++
FLAGS = -std=c++17

all: main

main: main.o Matrix.o
	$(CC) $(FLAGS) -o main main.o Matrix.o

test: test.x
	./test.x

test.x: test.o Matrix.o
	$(CC) $(FLAGS) -o test.x test.o Matrix.o

main.o: main.cpp Matrix.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp Matrix.h
	$(CC) $(FLAGS) -c test.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(FLAGS) -c Matrix.cpp

clean:
	rm -f *.o main test.x