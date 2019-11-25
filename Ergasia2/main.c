#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

int main(){
	int i, vec_sum, coords, k;
	char input[256];
	struct vec *vectors;
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
//	strcpy(input, "Ex2_Datasets/DataVectors_5_1000x500.csv");

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
		vectors[i].isMedoid = 0;
	}
	save_input(input, vectors);

	printf("Vectors= %d\tCoordinates = %d\n", vec_sum, coords);


	/***** Random selection of k points *****/
	k = 100;
	random_selection(vectors, vec_sum, k);

	int c=1;
	for(i=0; i<vec_sum; i++){
		if (vectors[i].isMedoid == 1){	
			printf("%d. %s\t", c, vectors[i].id);
			c++;
		}
	}

	return 0;
}
