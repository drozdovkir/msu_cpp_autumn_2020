CC = g++
FLAGS = -std=c++17

all: main

main: main.o TokenParser.o
	$(CC) $(FLAGS) -o main main.o TokenParser.o

test: test.x
	./test.x

test.x: test.o TokenParser.o
	$(CC) $(FLAGS) -o test.x test.o TokenParser.o

main.o: main.cpp TokenParser.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp TokenParser.h
	$(CC) $(FLAGS) -c test.cpp

TokenParser.o: TokenParser.cpp TokenParser.h
	$(CC) $(FLAGS) -c TokenParser.cpp

clean:
	rm -f *.o main test.x