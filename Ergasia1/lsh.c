#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, L, w, flag, vec_sum, coords, *a;
	char ch, *num, path[256];
	struct vec *vectors;
	struct h_func **h; 
	FILE *fp;

	k=4;
	L=5;
	w=4;															// Na kanoume dokimes!!!!
//	printf("Give the path to the data set:\n");
//	scanf("%s", path);
	strcpy(path, "siftsmall/input_small_id");

	count_input(path, &vec_sum, &coords);
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors=malloc(vec_sum*sizeof(struct vec));						// Kanw malloc gia na apothikeusw ta dianusmata
	for(i=0; i<vec_sum; i++){
		vectors[i].coord=malloc(coords*sizeof(int));
	}
	save_input(path, &vectors);

	h=malloc(L*sizeof(struct h_func *));							// Ftiaxnw tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){
		h[i]=malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s=malloc(coords&sizeof(int));
		}
	}
	srand(time(0));													// Dinw tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z]=rand()%w;
			}
		}
	}
	a=malloc(coords*sizeof(int));
	



/*	for(i=0; i<vec_sum; i++){										// Emfanizw olo to arxeio
		for(j=0; j<coords; j++){
			printf("%d ", vectors[i].coord[j]);
		}
		printf("\n\n");
	}
*/

	return 0;
}
