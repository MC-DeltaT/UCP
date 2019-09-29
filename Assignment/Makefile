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

EXEC = tictactoe
ALL_OBJ = main.o board.o interface.o log.o settings.o


$(EXEC) : $(ALL_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJ) -o $(EXEC)

main.o : main.c interface.h settings.h
	$(CC) $(CFLAGS) -c main.c -o main.o

board.o : board.h board.c
	$(CC) $(CFLAGS) -c board.c -o board.o

.PHONY: clean
clean :
	rm -f $(EXEC) $(ALL_OBJ)
