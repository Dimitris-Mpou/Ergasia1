OBJS = main.o input.o manhattan_distance.o initialization.o assignment.o update.o
SOURCE = main.c input.c manhattan_distance.c initialization.c assignment.c update.c
HEADER = structs.h functions.h
OUT = clusters
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

manhattan_distance.o: manhattan_distance.c
	$(CC) $(FLAG) manhattan_distance.c

initialization.o: initialization.c
	$(CC) $(FLAG) initialization.c

assignment.o: assignment.c
	$(CC) $(FLAG) assignment.c

update.o: update.c
	$(CC) $(FLAG) update.c

clean:
	rm -f $(OBJS) $(OUT)
