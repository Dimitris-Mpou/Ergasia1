#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

int main(){
	int i, vec_sum, coords, k, c;
	char input[256];
	struct vec *vectors;
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
	strcpy(input, "Ex2_Datasets/DataVectors_15_10000x500.csv");

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
	srand(time(0));							
	for(i=0; i<k; i++){
		do{							//Etsi wste na mh einai hdh metoid
			c = vec_sum*(rand() / (RAND_MAX +1.0));
		}
		while(vectors[c].isMedoid == 1);
		vectors[c].isMedoid = 1;
		//printf("%d. %s\t", i, vectors[c].id);
	}
	
	/* Dokimi gia to an ginetai kala h epilogh 
	   Ama thes dokimazeis alliws to svineis

	c=1;
	for(i=0; i<vec_sum; i++){
		if (vectors[i].isMedoid == 1){	
			printf("%d. %s\t", c, vectors[i].id);
			c++;
		}
	}*/
		
	printf("\n");
	return 0;
}
