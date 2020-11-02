CC = g++
FLAGS = -std=c++17

all: main

main: main.out
	./main.out

main.out: main.o TokenParser.o
	$(CC) $(FLAGS) -o main.out main.o TokenParser.o

test: test.out
	./test.out

test.out: test.o TokenParser.o
	$(CC) $(FLAGS) -o test.out test.o TokenParser.o

main.o: main.cpp TokenParser.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp TokenParser.h
	$(CC) $(FLAGS) -c test.cpp

TokenParser.o: TokenParser.cpp TokenParser.h
	$(CC) $(FLAGS) -c TokenParser.cpp

clean:
	rm -f *.o main.out test.out