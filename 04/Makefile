CC = g++
FLAGS = -std=c++17

all: main

main: main.out
	./main.out

main.out: main.o BigInt.o
	$(CC) $(FLAGS) -o main.out main.o BigInt.o

test: test.out
	./test.out

test.out: test.o BigInt.o
	$(CC) $(FLAGS) -o test.out test.o BigInt.o

main.o: main.cpp BigInt.h
	$(CC) $(FLAGS) -c main.cpp

test.o: test.cpp BigInt.h sums.txt diffs.txt prods.txt
	$(CC) $(FLAGS) -c test.cpp

BigInt.o: BigInt.cpp BigInt.h
	$(CC) $(FLAGS) -c BigInt.cpp

clean:
	rm -f *.o main.out test.out