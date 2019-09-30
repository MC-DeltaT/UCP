CC = gcc

CFLAGS = -ansi -pedantic -Wall -Werror -g -D DEBUG

EXEC = tictactoe_test
ALL_OBJ = main.o board_test.o common.o linked_list_test.o settings_test.o
EXT_OBJ = ../board.o ../common.o ../linked_list.o ../settings.o


$(EXEC) : $(ALL_OBJ) $(EXT_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJ) $(EXT_OBJ) -o $(EXEC)

main.o : main.c board_test.h linked_list_test.h settings_test.h
	$(CC) $(CFLAGS) -c main.c -o main.o

board_test.o : board_test.c board_test.h common.h ../board.h
	$(CC) $(CFLAGS) -c board_test.c -o board_test.o

linked_list_test.o : linked_list_test.c linked_list_test.h common.h ../linked_list.h
	$(CC) $(CFLAGS) -c linked_list_test.c -o linked_list_test.o

settings_test.o : settings_test.c settings_test.h common.h ../settings.h
	$(CC) $(CFLAGS) -c settings_test.c -o settings_test.o

.PHONY: clean
clean :
	rm -f $(EXEC) $(ALL_OBJ)
