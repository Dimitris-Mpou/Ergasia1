OBJS = main.o input.o manhattan_distance.o initialization.o assignment.o update.o lsh.o average.o modulo_calc.o concat.o factors.o hash.o
SOURCE = main.c input.c manhattan_distance.c initialization.c assignment.c update.c lsh.c average.c modulo_calc.c concat.c factors.c hash.c lsh.c
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

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

average.o: average.c
	$(CC) $(FLAG) average.c

modulo_calc.o: modulo_calc.c
	$(CC) $(FLAG) modulo_calc.c

concat.o: concat.c
	$(CC) $(FLAG) concat.c

factors.o: factors.c
	$(CC) $(FLAG) factors.c

hash.o: hash.c
	$(CC) $(FLAG) hash.c

clean:
	rm -f $(OBJS) $(OUT)
