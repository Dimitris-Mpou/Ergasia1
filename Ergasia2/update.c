#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>	//// Gia tin emfanisi twn kentrwn pou allaxan

void PAM(struct vec *vectors, struct vec *centers, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int k, int k_lsh, int L, char vec_asign){
	int i, j, z, min_pos, count, changes, flag;
	double dist, min, min_dist;	

	count = 0;
	changes = 1;
	while(changes != 0 && count < 100){
		changes = 0;	//////
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
			flag = 0;
			for(j=0; j<coords; j++){
				if(centers[i].coord[j] != vectors[min_pos].coord[j]){
					flag = 1;
					break;
				}
			}
			if(flag){		// Anathetoume to neo kentro	// isMedoid???
				for(j=0; j<coords; j++){
					centers[i].coord[j] = vectors[min_pos].coord[j];
				}
				changes++;				/////
			}
		}

		if(vec_asign == 1)
			Lloyds_assignment(vectors, centers, vec_sum, coords, k);
		else
			LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);

		count++;
		printf("In itteration %d: %d centers changed\n", count, changes);	/////
	}
}


void PAMean(struct vec *vectors, struct vec *centers, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int k, int k_lsh, int L, char vec_asign){
	int i, j, z, min_pos, count, cluster_size, changes, flag;
	double min, min_dist;
	struct vec prev_cent;

	prev_cent.coord = malloc(coords*sizeof(int));

	count = 0;
	changes = 1;
	while(changes != 0 && count < 100){
		changes = 0;							/////
		for(i=0; i<k; i++){					// Update centers
			for(j=0; j<coords; j++)			////
				prev_cent.coord[j] = centers[i].coord[j];
			for(j=0; j<coords; j++)
				centers[i].coord[j] = 0;
			cluster_size = 0;
			for(j=0; j<vec_sum; j++){
				if(vectors[j].nearest == i){
					cluster_size++;
					for(z=0; z<coords; z++){
						centers[i].coord[z] += vectors[j].coord[z];
					}
				}
			}
			for(j=0; j<coords; j++)
				centers[i].coord[j] = centers[i].coord[j] / cluster_size;
			
			flag = 0;
			for(j=0; j<coords; j++){		///
				if(centers[i].coord[j] != prev_cent.coord[j]){
					flag = 1;
					break;
				}
			}
			if(flag)
				changes++;		////
		}

		if(vec_asign == 1)
			Lloyds_assignment(vectors, centers, vec_sum, coords, k);
		else
			LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);

		count++;
		printf("In itteration %d: %d centers changed\n", count, changes);	/////
	}
}

void PAMean_curves(struct curve *curves, struct curve *centers_curve, int curves_sum, int k){
	int i, j, lamda, n, random_sequence, sequence_num, counter, flag;
	struct curve C;
	
	for(i=0; i<k; i++){
		lamda = 0;						//Ypologizoume to lamda
		n=0;
		for(j=0; j<curves_sum; j++){
			if(curves[j].nearest == i){
				lamda += curves[j].noPoints;
				n++;
			}
		}
		lamda = lamda/n;
		printf("Cluster %d\t lamda:%d\n", i, lamda);
		C.points = malloc(lamda*sizeof(struct point));
		srand(time(0));						//Vriskoume thn tuxaia upoakolouthia
		flag = 1;
		do{
			random_sequence = n*(rand() / (RAND_MAX +1.0));
			counter=-1;
			for(j=0; j<curves_sum; j++){
				if(curves[j].nearest == i){
					counter++;
					if(counter == random_sequence){		//Eimaste sthn tuxaia akolouthia S0
						if(curves[j].noPoints >= lamda){
							flag = 0;
							sequence_num = j;
						}
						break;
					}
				}
			}
		}while(flag);

		random_subsequence(curves[sequence_num], &C, lamda);
		
	}
}

void random_subsequence(struct curve a, struct curve *b, int lamda){
	int i, *random_points;

	random_points = malloc(lamda*sizeof(int));
	srand(time(0));
	random_points[0] = 0;
	for(i=1; i<lamda; i++){
		do{
			random_points[i] = a.noPoints*(rand() / (RAND_MAX +1.0));
		}while(random_points[i] <= random_points[i-1] || random_points[i] > a.noPoints-(lamda-i));
	}

	b->noPoints = lamda;
	for(i=0; i<lamda; i++){
		b->points[i].x = a.points[random_points[i]].x;
		b->points[i].y = a.points[random_points[i]].y;
	}
}
