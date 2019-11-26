#include "structs.h"
#include "functions.h"

void Lloyds_assignment(struct vec *vectors, struct vec *centers, int vec_sum, int coords, int k){
	int i, j;
	double min_dist;

	for(i=0; i<vec_sum; i++){
		min_dist = 10000000.0;
		
		for(j=0; j<k; j++){
			if( manhattan_distance(vectors[i], centers[j], coords) < min_dist ){
				vectors[i].nearest_centroid = &centers[j];
				min_dist = manhattan_distance(vectors[i], centers[j], coords);
			}
		}
	}
}
