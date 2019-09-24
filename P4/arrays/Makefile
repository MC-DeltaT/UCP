CC = gcc
CFLAGS = -pedantic -ansi -Wall -Werror
MAIN_OBJ = util.o main.o
MAIN = main

$(MAIN) : $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(MAIN_OBJ) -o $(MAIN)

util.o : util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

clean :
	rm -f $(MAIN) $(MAIN_OBJ)
