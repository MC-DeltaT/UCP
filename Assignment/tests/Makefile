COMPILER = gcc
CFLAGS = -ansi -pedantic -Wall -Werror -g -D DEBUG
CC = $(COMPILER) $(CFLAGS)

EXEC = tictactoe_test
TEST_OBJ = main.o board_test.o common.o linked_list_test.o log_test.o settings_test.o

# Required object files from main build (relative to this directory).
REQ_OBJ = ../board.o ../linked_list.o ../log.o ../settings.o ../common.o


$(EXEC) : $(TEST_OBJ) $(REQ_OBJ)
	$(CC) $(TEST_OBJ) $(REQ_OBJ) -o $(EXEC)

main.o : main.c board_test.h linked_list_test.h settings_test.h
	$(CC) -c main.c -o main.o

common.o : common.c common.h
	$(CC) -c common.c -o common.o

board_test.o : board_test.c board_test.h common.h ../board.h ../common.h
	$(CC) -c board_test.c -o board_test.o

linked_list_test.o : linked_list_test.c linked_list_test.h common.h ../linked_list.h
	$(CC) -c linked_list_test.c -o linked_list_test.o

log_test.o : log_test.c log_test.h common.h ../log.h ../common.h
	$(CC) -c log_test.c -o log_test.o

settings_test.o : settings_test.c settings_test.h common.h ../settings.h
	$(CC) -c settings_test.c -o settings_test.o

# Resolves dependencies in the main build directory (../) and makes them
# properly using that makefile.
../%.o : ../%.c
	$(MAKE) -C ../ $(@:../%=%)

.PHONY: clean
clean :
	rm -f $(EXEC) $(TEST_OBJ)
