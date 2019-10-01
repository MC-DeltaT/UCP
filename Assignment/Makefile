COMPILER = gcc

CFLAGS = -ansi -pedantic -Wall -Werror

ifdef DEBUG
CFLAGS += -g -D DEBUG
endif
ifdef SECRET_MODE
CFLAGS += -D SECRET_MODE
endif
ifdef EDITOR_MODE
CFLAGS += -D EDITOR_MODE
endif

CC = $(COMPILER) $(CFLAGS)

EXEC = tictactoe
ALL_OBJ = main.o board.o interface.o linked_list.o log.o settings.o


$(EXEC) : $(ALL_OBJ)
	$(CC) $(ALL_OBJ) -o $(EXEC)

main.o : main.c interface.h settings.h
	$(CC) -c main.c -o main.o

board.o : board.c board.h
	$(CC) -c board.c -o board.o

common.o : common.c common.h
	$(CC) -c common.c -o common.o

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c -o linked_list.o

log.o : log.c log.h linked_list.h
	$(CC) -c log.c -o log.o

settings.o : settings.c settings.h common.h
	$(CC) -c settings.c -o settings.o

.PHONY: clean
clean :
	rm -f $(EXEC) $(ALL_OBJ)
