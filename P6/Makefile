CC = gcc
CFLAGS = -ansi -Wall -Werror -pedantic

.PHONY: all
all : copyfile.c logreader.c
	make copyfile; make logreader

copyfile : copyfile.c
	$(CC) $(CFLAGS) copyfile.c -o copyfile

logreader : logreader.c
	$(CC) $(CFLAGS) logreader.c -o logreader

.PHONY: clean
clean :
	rm -f copyfile logreader
