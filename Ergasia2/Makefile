OBJS = main.o input.o random_selection.o manhattan_distance.o k_means_plus_plus.o
SOURCE = main.c input.c random_selection.c manhattan_distance.c k_means_plus_plus.o
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

manhattan_distance.o: manhattan_distance.c
	$(CC) $(FLAG) manhattan_distance.c

k_means_plus_plus.o: k_means_plus_plus.c
	$(CC) $(FLAG) k_means_plus_plus.c

clean:
	rm -f $(OBJS) $(OUT)
