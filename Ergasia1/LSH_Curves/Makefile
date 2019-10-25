OBJS = main.o input.o dtw.o #average.o modulo_calc.o concut.o factors.o hash.o lsh.o write_output.o
SOURCE = main.c input.c dtw.c #average.c modulo_calc.c concut.c factors.c hash.c lsh.c write_output.c
HEADER = headers.h functions.h
OUT = curves
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

dtw.o: dtw.c
	$(CC) $(FLAG) dtw.c

#average.o: average.c
#	$(CC) $(FLAG) average.c

#modulo_calc.o: modulo_calc.c
#	$(CC) $(FLAG) modulo_calc.c

#concut.o: concut.c
#	$(CC) $(FLAG) concut.c

#factors.o: factors.c
#	$(CC) $(FLAG) factors.c

#hash.o: hash.c
#	$(CC) $(FLAG) hash.c

#lsh.o: lsh.c
#	$(CC) $(FLAG) lsh.c

#write_output.o: write_output.c
#	$(CC) $(FLAG) write_output.c

clean:
	rm -f $(OBJS) $(OUT)
