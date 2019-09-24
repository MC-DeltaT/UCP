CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
DOWNLOAD_OBJ = download.o download_stats.o
DOWNLOAD_EXEC = download
Q1_EXEC = q1

ifdef ALL_STATS
DOWNLOAD_FLAGS = -D ALL_STATS
endif

$(DOWNLOAD_EXEC) : $(DOWNLOAD_OBJ)
	$(CC) $(CFLAGS) $(DOWNLOAD_OBJ) -o $(DOWNLOAD_EXEC)

download.o : download.c download_stats.h
	$(CC) $(CFLAGS) $(DOWNLOAD_FLAGS) -c download.c -o download.o

download_stats.o : download_stats.c download_stats.h
	$(CC) $(CFLAGS) -c download_stats.c -o download_stats.o

$(Q1_EXEC) : q1.c
	$(CC) $(CFLAGS) q1.c -o $(Q1_EXEC)

clean :
	rm -f $(DOWNLOAD_EXEC) $(DOWNLOAD_OBJ) $(Q1_EXEC)
