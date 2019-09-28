CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
ifdef DEBUG
CFLAGS += -g
endif
ifdef SECRET_MODE
CFLAGS += -D SECRET_MODE
endif
ifdef EDITOR_MODE
CFLAGS += -D EDITOR_MODE
endif

tictactoe : main.o interface.o log.o settings.o
	$(CC) $(CFLAGS) main.o interface.o -o tictactoe

main.o : main.c interface.h settings.h
	$(CC) $(CFLAGS) -c main.c -o main.o

board.o : board.h board.c
	$(CC) $(CFLAGS) -c board.c -o board.o

.PHONY: clean
clean :
	rm -f tictactoe board.o interface.o log.o main.o settings.o
