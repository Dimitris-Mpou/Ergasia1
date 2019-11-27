#include <stdlib.h>
#include "structs.h"
#include "functions.h"

void PAM(struct vec *vectors, int *centers, int vec_sum, int coords, int k){
	int i, j, z, *min_pos;
	double dist, *min;

	min = malloc(k*sizeof(double));
	for(i=0; i<k; i++)
		min[i] = 10000000.0;
	min_pos = malloc(k*sizeof(int));
	for(i=0; i<k; i++)
		min_pos[i] = centers[i];

	for(i=0; i<k; i++){
		for(j=0; j<vec_sum; j++){
			if(vectors[j].nearest_centroid == centers[i]){
				dist = 0.0;
				for(z=0; z<vec_sum; z++){
					if(vectors[z].nearest_centroid == centers[i]){
						dist += manhattan_distance(vectors[j], vectors[z], coords);
					}
				}
				if(dist < min[i]){
					min[i] = dist;
					min_pos[i] = j;
				}
			}
		}
	}
	// min_pos has new centers
	for(i=0; i<k; i++){
		centers[i] = min_pos[i];
	}
}
