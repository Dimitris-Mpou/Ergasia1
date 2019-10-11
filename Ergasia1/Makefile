OBJS = lsh.o input.o
SOURCE = lsh.c
HEADER = headers.h functions.h
OUT = lsh
CC = gcc
FLAG = -c

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

input.o: input.c
	$(CC) $(FLAG) input.c

clean:
	rm -f $(OBJS) $(OUT)
