#include "structs.h"
#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Lloyds_assignment(struct vec *vectors, int *centers, int vec_sum, int coords, int k){
	int i, j;
	double min_dist;
	
	for(i=0; i<vec_sum; i++){

		min_dist = 10000000.0;		
		for(j=0; j<k; j++){
			if( manhattan_distance(vectors[i], vectors[centers[j]], coords) < min_dist ){
				vectors[i].nearest = j;
				min_dist = manhattan_distance(vectors[i], vectors[centers[j]], coords);
			}
		}
		/*
		min_dist = 10000000.0;
		for(j=0; j<k; j++){
			if( manhattan_distance(vectors[i], vectors[centers[j]], coords) < min_dist && vectors[i].nearest != j){
				vectors[i].second_nearest = j;
				min_dist = manhattan_distance(vectors[i], vectors[centers[j]], coords);
			}
		}
		*/
	}
}

void LSH_assignment(struct vec *vectors, int vec_sum, int coords){
	int k, L, w, r;
	
	k = 4;
	L = 5;

	r = average_dist(vec_sum, coords, vectors);			// Kwdikas gia ton upologismo tou r wste na thesoume w = 4*r
	printf("r=%d\n", r);
	w = 4*r;

	lsh(vectors, vec_sum, coords, k, L, w);
}
