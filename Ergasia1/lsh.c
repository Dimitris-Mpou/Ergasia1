#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, flag, vec_sum, coords;
	char ch, *num, path[256];
	struct vec *vectors;
	FILE *fp;

	printf("Give the path to the data set:\n");
	scanf("%s", path);

	count_input(path, &vec_sum, &coords);
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors=malloc(vec_sum*sizeof(struct vec));						// Kanw malloc gia na apothikeusw ta dianusmata
	for(i=0; i<vec_sum; i++){
		vectors[i].coord=malloc(coords*sizeof(int));
	}
	save_input(path, &vectors);

/*	for(i=0; i<vec_sum; i++){										// Emfanizw olo to arxeio
		for(j=0; j<coords; j++){
			printf("%d ", vectors[i].coord[j]);
		}
		printf("\n\n");
	}	Dokimiii
*/

	return 0;
}
