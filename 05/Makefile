CC = g++
FLAGS = -std=c++17

all: main

main: main.out
	./main.out

main.out: main.o
	$(CC) $(FLAGS) -o main.out main.o

test: test.out
	./test.out

test.out: test.o
	$(CC) $(FLAGS) -o test.out test.o

main.o: main.cpp Serializer.h MyStruct.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp Serializer.h MyStruct.h
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o main.out test.out tests.txt