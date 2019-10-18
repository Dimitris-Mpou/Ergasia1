#include <stdlib.h>
#include "headers.h"

float average_dist(int vec_sum, int coords, struct vec *vectors){
	int i, j, z, dist, min, min_pos, aver;

	aver=0;
	min=1000000;
	min_pos=-1;
	dist=0;
	for(z=0; z<100; z++){
		for(i=0; i<vec_sum; i++){
			for(j=0; j<coords; j++){
				dist+=abs(vectors[z].coord[j]-vectors[i].coord[j]);
			}
			if(min>dist && z!=i){
				min=dist;
				min_pos=i;
			}
			dist=0;
		}
		aver+=min;
		min=1000000;
	}
	return (float) aver/100;
}


void query_knn(int vec_sum, int quer_sum, int coords, struct vec *vectors, struct vec *queries, int *knn_results){
	int i, j, z, dist, min, min_pos, aver;

	min=1000000;
	min_pos=-1;
	dist=0;
	for(z=0; z<quer_sum; z++){
		for(i=0; i<vec_sum; i++){
			for(j=0; j<coords; j++){
				dist+=abs(queries[z].coord[j]-vectors[i].coord[j]);
			}
			if(min>dist){
				min=dist;
				min_pos=i;
			}
			dist=0;
		}
		min=1000000;
		knn_results[z]=min_pos;
	}

}
