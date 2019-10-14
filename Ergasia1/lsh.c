#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, L, w, flag, vec_sum, coords, *a, m, M, g;
	char ch, *num, path[256];
	float f;
	struct vec *vectors;
	struct h_func **h; 
	FILE *fp;

	k=4;
	L=5;
	w=4*880;														// Na kanoume dokimes!!!!
	//printf("Give the path to the data set:\n");
	//scanf("%s", path);
	strcpy(path, "siftsmall/input_small_id");

	count_input(path, &vec_sum, &coords);
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors=malloc(vec_sum*sizeof(struct vec));						// Kanw malloc gia na apothikeusw ta dianusmata
	for(i=0; i<vec_sum; i++){
		vectors[i].coord=malloc(coords*sizeof(int));
	}
	save_input(path, &vectors);
	

	printf("%f\n", average_dist(vec_sum, coords, &vectors));		// Aplos kwdikas anazitisis gia ton evresi tis mesis apostasis apo ton plisiestero 												geitona
	

	h=malloc(L*sizeof(struct h_func *));							// Ftiaxnw tis sunartiseis h pou kathe mia tha exei ola ta s 														apothikeumena gia to query
	for(i=0; i<L; i++){
		h[i]=malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s=malloc(coords*sizeof(int));
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
	/* Gia tin dimiourgia tou 1ou hashtable : */
	
	m = 4;
	M = 128;
	for(z=0; z<L; z++){
		for(i=0; i<k; i++){								
			h[z][i].h_sum = 0;
			for(j=0; j<coords; j++){
				f = (float) (vectors[i].coord[j] - h[z][i].s[j]) / w;			//Briskw kathe a[i]
				a[j]=floor(f) + 2;							//Efarmozw to floor kai ta kanw thetika
				g = modulo_calc(m, (coords-1) - j, M);
				//printf("%d ", g);
				h[z][i].h_sum += a[j] * g;						//Kanw mod se kathe paragonta kai athroizw  !! m^.. !!
			}
			h[z][i].h_sum = h[z][i].h_sum % M;						//Kanw mod kai so oloklhro to athroisma
			//printf("%d\t", h[z][i].h_sum);
			printf("\n");
			
		}
		printf("\n");
	}


/*	for(i=0; i<vec_sum; i++){										// Emfanizw olo to arxeio
		for(j=0; j<coords; j++){
			printf("%d ", vectors[i].coord[j]);
		}
		printf("\n\n");
	}
*/

	return 0;
}
