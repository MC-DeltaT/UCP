CC = gcc

CFLAGS = -ansi -pedantic -Wall -Werror -g -D DEBUG

EXEC = tictactoe_test
ALL_OBJ = main.o settings_test.o common.o
EXT_OBJ = ../settings.o ../common.o


$(EXEC) : $(ALL_OBJ) $(EXT_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJ) $(EXT_OBJ) -o $(EXEC)

main.o : main.c settings_test.h
	$(CC) $(CFLAGS) -c main.c -o main.o

settings_test.o : settings_test.c settings_test.h common.h ../settings.h
	$(CC) $(CFLAGS) -c settings_test.c -o settings_test.o

.PHONY: clean
clean :
	rm -f $(EXEC) $(ALL_OBJ)
