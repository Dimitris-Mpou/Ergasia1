#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

int main(){
	int i, j, vec_sum, coords, k, *centers;
	char input[256];
	struct vec *vectors;
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
//	strcpy(input, "Ex2_Datasets/DataVectors_5_1000x500.csv");

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume

	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
		vectors[i].isMedoid = 0;
		vectors[i].nearest = -1;
	}
	save_input(input, vectors);

	printf("Vectors= %d\tCoordinates = %d\n", vec_sum, coords);


	/****** Initialize ***********/
	k = 20;
	centers = malloc(k*sizeof(int));
//	random_selection(vectors, vec_sum, k);
	k_means_plus_plus(vectors, vec_sum, k, coords);
	
	int c=0;
	for(i=0; i<vec_sum; i++){
		if (vectors[i].isMedoid == 1){	
			centers[c] = i;
			c++;
		}
	}

	/****** Assignment ***********/
	Lloyds_assignment(vectors, centers, vec_sum, coords, k);

	for(i=0; i<k; i++){
		printf("%d, %s\t", i, vectors[centers[i]].id);
	}
	printf("\n\n");

	/****** Update ***********/
	PAM(vectors, centers, vec_sum, coords, k);


	return 0;
}
