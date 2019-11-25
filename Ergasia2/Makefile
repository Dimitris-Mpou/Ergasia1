OBJS = main.o input.o random_selection.o
SOURCE = main.c input.c random_selection.c
HEADER = structs.h functions.h
OUT = curve
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

random_selection.o: random_selection.c
	$(CC) $(FLAG) random_selection.c

clean:
	rm -f $(OBJS) $(OUT)
