CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
MAIN_OBJ = numbers.o order.o user_input.o
MAIN_EXEC = numbers


$(MAIN_EXEC) : $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(MAIN_OBJ) -o $(MAIN_EXEC)

numbers.o : numbers.c order.h user_input.h
	$(CC) $(CFLAGS) -c numbers.c -o numbers.o

order.o : order.c order.h
	$(CC) $(CFLAGS) -c order.c -o order.o

user_input.o : user_input.c user_input.h
	$(CC) $(CFLAGS) -c user_input.c -o user_input.o

clean :
	rm -f $(MAIN_EXEC) $(MAIN_OBJ)
