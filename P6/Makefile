CC = gcc
CFLAGS = -ansi -Wall -Werror -pedantic
ifdef DEBUG
CFLAGS += -g -D DEBUG
endif


.PHONY: all
all : copyfile.c logreader.c display.o plot.o
	make copyfile; make logreader; make display

copyfile : copyfile.c
	$(CC) $(CFLAGS) copyfile.c -o copyfile

logreader : logreader.c
	$(CC) $(CFLAGS) logreader.c -o logreader

display : display.o plot.o
	$(CC) $(CFLAGS) display.o plot.o -o display

generate : generate.o randomarray.o
	$(CC) $(CFLAGS) generate.o randomarray.o -o generate

display.o : display.c plot.h
	$(CC) $(CFLAGS) -c display.c -o display.o

plot.o : plot.c plot.h
	$(CC) $(CFLAGS) -c plot.c -o plot.o

generate.o : generate.c randomarray.h
	$(CC) $(CFLAGS) -c generate.c -o generate.o

randomarray.o : randomarray.c randomarray.h
	$(CC) $(CFLAGS) -c randomarray.c -o randomarray.o

.PHONY: clean
clean :
	rm -f copyfile logreader display generate display.o plot.o generate.o randomarray.o
