#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structs.h"
#include "functions.h"



void Lloyds_assignment(struct vec *vectors, struct vec *centers, int vec_sum, int coords, int k){
	int i, j;
	double min_dist, dist;
	
	for(i=0; i<vec_sum; i++){

		min_dist = 10000000.0;		
		for(j=0; j<k; j++){
			dist = manhattan_distance(vectors[i], centers[j], coords);
			if(dist  < min_dist ){
				vectors[i].nearest = j;
				min_dist = dist;
			}
		}
		/*
		min_dist = 10000000.0;
		for(j=0; j<k; j++){
			dist = manhattan_distance(vectors[i], centers[j], coords);
			if( dist < min_dist && vectors[i].nearest != j){
				vectors[i].second_nearest = j;
				min_dist = dist;
			}
		}
		*/
	}
}

void LSH_assignment(struct vec *vectors, struct vec *centers, int vec_sum, int coords, int k_clusters){
	int i, j, z, k, L, w, quer_sum, m, M, *m_factors, TableSize, *search_results, *lsh_results;
	float r;
	struct vec  *queries;
	struct h_func **h; 
	struct list_node ***HashTables;

	/**** Initialize LSH structures and variables ****/

	k = 4;
	L = 5;
	w = 4500;
	m = 5;
	M = pow(2, 32/k);

	lsh_results = malloc(k_clusters*sizeof(int));

	h = malloc(L*sizeof(struct h_func *));			// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){	
		h[i] = malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));												// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = w*(rand() / (RAND_MAX +1.0));
			}
		}
	}
	
	TableSize = vec_sum/8;										// Kanoume malloc gia tous L Hashtables
	HashTables = malloc(L*sizeof(struct list_node **));
	for(i=0; i<L; i++){
		HashTables[i] = malloc(TableSize*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){											// Ola ta buckets twn hashtables dixnoun NULL
		for(j=0; j<TableSize; j++){
			HashTables[i][j] = NULL;
		}
	}

	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	/**** LSH ***/

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize);		// Ekteloume to lsh gia to input data

	for(i=0; i<k_clusters; i++){
//		lsh_results[i] = lsh_search(vectors, centers[i], h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize);
	}
}
