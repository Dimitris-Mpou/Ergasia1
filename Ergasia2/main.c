#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

int main(){
	int i, j, vec_sum, coords, k;
	char input[256];
	struct vec *vectors, *centers;
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
//	strcpy(input, "Ex2_Datasets/DataVectors_5_1000x500.csv");

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
		vectors[i].isMedoid = 0;
		vectors[i].nearest_centroid = NULL;
	}
	save_input(input, vectors);

	printf("Vectors= %d\tCoordinates = %d\n", vec_sum, coords);

	k = 50;
	centers = malloc(k*sizeof(struct vec));
	random_selection(vectors, vec_sum, k);
//	k_means_plus_plus(vectors, vec_sum, k, coords);
	
	int c=0;
	for(i=0; i<vec_sum; i++){
		if (vectors[i].isMedoid == 1){	
			centers[c] = vectors[i];
			c++;
		}
	}

	/****** Assignment ***********/
	Lloyds_assignment(vectors, centers, vec_sum, coords, k);

	for(i=0; i<k; i++){
		printf("%d, %s\t", i, centers[i].id);
	}

	printf("\n\n");
	
	for(i=0; i<vec_sum; i++){
		printf("%d, %s -> %s\t", i, vectors[i].id, vectors[i].nearest_centroid->id);
	}

	printf("\n");
	
	return 0;
}
