CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.c)


all : game

main.o : main.c functions.h
	gcc -c main.c -o main.o

functions.o : functions.c functions.h
	$(CC)  -c functions.c -o functions.o

game : main.o functions.o
	gcc main.o functions.o -o game

clean :
	rm -f *.o
	rm -f game
