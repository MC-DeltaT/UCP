CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
ifdef DEBUG
CFLAGS += -g
endif

.PHONY: all
all : journalreader.c
	make journalreader

journalreader : journalreader.c
	$(CC) $(CFLAGS) journalreader.c -o journalreader

.PHONY: clean
clean :
	rm -f journalreader
