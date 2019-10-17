OBJS = main.o input.o average.o modulo_calc.o concut.o factors.o hash.o lsh.o
SOURCE = lsh.c
HEADER = headers.h functions.h
OUT = lsh
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

average.o: average.c
	$(CC) $(FLAG) average.c

modulo_calc.o: modulo_calc.c
	$(CC) $(FLAG) modulo_calc.c

concut.o: concut.c
	$(CC) $(FLAG) concut.c

factors.o: factors.c
	$(CC) $(FLAG) factors.c

hash.o: hash.c
	$(CC) $(FLAG) hash.c

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

clean:
	rm -f $(OBJS) $(OUT)
