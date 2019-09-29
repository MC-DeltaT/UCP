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

board.o : board.c board.h
	$(CC) $(CFLAGS) -c board.c -o board.o

settings.o : settings.c settings.h common.h
	$(CC) $(CFLAGS) -c settings.c -o settings.o

common.o : common.c common.h
	$(CC) $(CFLAGS) -c common.c -o common.o

.PHONY: clean
clean :
	rm -f $(EXEC) $(ALL_OBJ)
