CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
ifdef DEBUG
CFLAGS += -g
endif

.PHONY: all
all : journalreader.c linked_list_test.o linked_list.o
	make journalreader; make linked_list_test

journalreader : journalreader.c
	$(CC) $(CFLAGS) journalreader.c -o journalreader

linked_list_test : linked_list_test.o linked_list.o
	$(CC) $(CFLAGS) linked_list_test.o linked_list.o -o linked_list_test

linked_list_test.o : linked_list_test.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list_test.c -o linked_list_test.o

linked_list.o : linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c -o linked_list.o

.PHONY: clean
clean :
	rm -f journalreader linked_list_test linked_list_test.o linked_list.o
