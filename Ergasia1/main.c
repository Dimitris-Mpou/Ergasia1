#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, t, L, w, vec_sum, coords, m, M, *m_factors, TableSize, sum, *knn_results;
	unsigned int g;
	char ch, *num, path[256];
	float r;
	struct vec *vectors;
	struct h_func **h; 
	struct list_node ***HashTables, *cur;
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
	save_input(path, vectors);

	knn_results=malloc(50*sizeof(int));
	r = average_dist(vec_sum, coords, vectors, knn_results);
	printf("r = %f\n", r);		// Aplos kwdikas anazitisis gia ton evresi tis mesis apostasis apo ton plisiestero geitona

	h=malloc(L*sizeof(struct h_func *));				// Ftiaxnw tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){
		h[i]=malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s=malloc(coords*sizeof(int));
		}
	}
	srand(time(0));							// Dinw tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z]=rand()%w;
			}
		}
	}

	/* Gia tin dimiourgia twn hashtables : */
	
	TableSize=vec_sum/8;
	HashTables=malloc(L*sizeof(struct list_node **));
	for(i=0; i<L; i++){
		HashTables[i]=malloc(TableSize*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){
		for(j=0; j<TableSize; j++){
			HashTables[i][j]=NULL;
		}
	}
	
	m = 5;
	M = pow(2, 32/k);

	m_factors=malloc(coords*sizeof(int));
	factors(m, M, coords, m_factors);

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize);
	sum=0;
	printf("Actual Result\tLSH Result\n\n");
	for(i=0; i<50; i++){
		printf("%d\t\t%d\n", t=knn_results[i], z=lsh_search(vectors, vectors[i], h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize));
		if(t==z){sum++;}
	}
	printf("Score: %d / 50\n", sum);

	return 0;
}
