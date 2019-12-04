OBJS = main.o input.o manhattan_distance.o initialization.o assignment.o update.o lsh.o lsh_functions.o
SOURCE = main.c input.c manhattan_distance.c initialization.c assignment.c update.c lsh.c lsh_functions.c
HEADER = structs.h functions.h
OUT = cluster
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

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

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

lsh_functions.o: lsh_functions.c
	$(CC) $(FLAG) lsh_functions.c

clean:
	rm -f $(OBJS) $(OUT)
