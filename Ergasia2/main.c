#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

int main(){
	int i, vec_sum, coords;
	char input[256];
	struct vec *vectors;
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
	strcpy(input, "Ex2_Datasets/DataVectors_15_10000x500.csv");

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
	}
	save_input(input, vectors);

	printf("Vectors= %d\tCoordinates = %d\n", vec_sum, coords);

	return 0;
}
