#include <time.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>

void k_means_plus_plus(struct vec *vectors, int vec_sum, int k, int coords){
	int i, j, c, centroid_count, *centroids;
	double *P, *D, dist;

	D = malloc((vec_sum-1)*sizeof(double));
	P = malloc((vec_sum-1)*sizeof(double));
	centroids = malloc(k*sizeof(int));

	srand(time(0));							
	centroids[0] = vec_sum*(rand() / (RAND_MAX +1.0));
	vectors[centroids[0]].isMedoid = 1;
	centroid_count = 1;
	
	for(i=0; i<vec_sum; i++){			// Gia kathe simeio
		if(vectors[i].isMedoid == 0){	// Pou den einai kentroides
			D[i] = manhattan_distance(vectors[i], vectors[centroids[0]], coords);	// Ypologismos D[i]
			for(j=1; j<centroid_count; j++){
				dist = manhattan_distance(vectors[i], vectors[centroids[j]], coords);
				if(dist < D[i])
					D[i] = dist;
			}
			if(i==0){			// Count P[i]
				P[0] = D[0]*D[0];
			}else if(i==1 && centroids[0]==0){	// An to dianusma 0 itan to 1o centroid
				P[0] = D[1]*D[1];
			}else{
				P[i] = P[i-1] + D[i]*D[i];
			}
		}else if(i>0){		// Etsi an ena dianusma einai centroid to P[i] tou dianusmatos periexei to P[i-1]
			P[i] = P[i-1];
		}
	}
	// Epilogi epomenou centroid vasi twn P[i]
	//Epanalipsi olou mexris otou centroid_count=k
}
