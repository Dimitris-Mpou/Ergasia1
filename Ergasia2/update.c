#include <stdlib.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>	//// Gia tin emfanisi twn kentrwn pou allaxan

void PAM(struct vec *vectors, int *centers, int vec_sum, int coords, int k){
	int i, j, z, min_pos, count;
	double dist, min, min_dist;

	int change;	//// Gia tis dokimes

	count = 0;
	while(count < 10){
		change = 0;	//////
		for(i=0; i<k; i++){					// Update centers
			min = 10000000.0;
			for(j=0; j<vec_sum; j++){
				if(vectors[j].nearest == i){
					dist = 0.0;
					for(z=0; z<vec_sum; z++){
						if(vectors[z].nearest == i){
							dist += manhattan_distance(vectors[j], vectors[z], coords);
						}
					}
					if(dist < min){
						min = dist;
						min_pos = j;
					}
				}
			}
			if(centers[i] != min_pos){
				vectors[centers[i]].isMedoid = 0;
				vectors[min_pos].isMedoid = 1;
				centers[i] = min_pos;
				change++;				/////
			}
		}

		for(i=0; i<vec_sum; i++){		// Update assignment (Xwris tin paradoxi tou kuriou Emiri)
			min_dist = manhattan_distance(vectors[i], vectors[ centers[vectors[i].nearest] ], coords);
			for(j=0; j<k; j++){
				if(manhattan_distance(vectors[i], vectors[ centers[j] ], coords) < min_dist )
					vectors[i].nearest = j;
					min_dist = manhattan_distance(vectors[i], vectors[centers[j]], coords);
			}
		}
	
		count++;
		printf("In itteration %d: %d centers changed\n", count, change);	/////
	}
}
