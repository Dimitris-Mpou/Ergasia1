#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main(void){
	int i, j, z, vec_sum, coords, k, L, k_lsh, w, m, M, *m_factors;
	char input[256];
	struct vec *vectors, *centers;
	struct h_func **h; 
	struct list_node ***HashTables;
	
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

	k = 100;
	centers = malloc(k*sizeof(struct vec));
	for(i=0; i<k; i++)
		centers[i].coord = malloc(coords*sizeof(double));
	random_selection(vectors, vec_sum, k);
//	k_means_plus_plus(vectors, vec_sum, k, coords);
	
	int c=0;
	for(i=0; i<vec_sum; i++){				// isMedoid, nearest??
		if (vectors[i].isMedoid == 1){
			for(j=0; j<coords; j++){
				centers[c].coord[j] = vectors[i].coord[j];
			}
			c++;
		}
	}

	/****** Assignment ***********/

//	Lloyds_assignment(vectors, centers, vec_sum, coords, k);

	/*	Lsh Initialize	*/

	L = 5;
	k_lsh = 4;
	w = 4500;	
	m = 5;
	M = pow(2, 32/k_lsh);

	h = malloc(L*sizeof(struct h_func *));						// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){	
		h[i] = malloc(k_lsh*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k_lsh; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));												// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k_lsh; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = w*(rand() / (RAND_MAX +1.0));
			}
		}
	}
	HashTables = malloc(L*sizeof(struct list_node **));			// Kanoume malloc gia tous L Hashtables
	for(i=0; i<L; i++){
		HashTables[i] = malloc(vec_sum/8*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){											// Ola ta buckets twn hashtables dixnoun NULL
		for(j=0; j<vec_sum/8; j++){
			HashTables[i][j] = NULL;
		}
	}

	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k_lsh, L, w, vec_sum/8);		// Ekteloume to lsh gia to input data
	
	LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k);

	/****** Update ***********/

	//PAM(vectors, centers, vec_sum, coords, k);

//	PAMean(vectors, centers, vec_sum, coords, k);


	return 0;
}
