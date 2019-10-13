#include <stdlib.h>
#include "headers.h"

float average_dist(int vec_sum, int coords, struct vec **vectors){
	int i, j, z, dist, min, aver;

	aver=0;
	min=1000000;
	dist=0;
	for(z=0; z<50; z++){
		for(i=0; i<vec_sum; i++){
			for(j=0; j<coords; j++){
				dist+=abs((*vectors)[z].coord[j]-(*vectors)[i].coord[j]);
			}
			if(min>dist && z!=i){min=dist;}
			dist=0;
		}
		aver+=min;
		min=1000000;
	}
	return (float) aver/50;
}
