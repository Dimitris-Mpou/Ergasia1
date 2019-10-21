#include <stdlib.h>
#include <time.h>
#include "headers.h"
#include <math.h>

void cube_train(unsigned int **g, struct list_node ***f, struct list_node **cube, int vec_sum, int d){
	int i, j, hash_pos, cube_pos;
	struct list_node *cur;

	srand(time(0));
	for(i=0; i<vec_sum; i++){
		cube_pos = 0;
		for(j=0; j<d; j++){
			hash_pos = g[i][j] % 4999;
			if(f[j][hash_pos ] == NULL){
				f[j][hash_pos] = malloc(sizeof(struct list_node));
				f[j][hash_pos]->next = NULL;
				f[j][hash_pos]->g = g[i][j];
				f[j][hash_pos]->vec_pos = rand() % 2;
				cube_pos += f[j][hash_pos]->vec_pos*pow(2,d-1 -j);		// Den apothikeuoume to diadiko string alla to xrisimopoume gia na broume se poia korifi tou kubou tha paei to dianusma
			}else{
				cur = f[j][hash_pos];
				while(cur->next!=NULL && cur->g!=g[i][j]){
					cur = cur->next;
				}
				if(cur->g != g[i][j]){
					cur->next = malloc(sizeof(struct list_node));
					cur->next->g = g[i][j];
					cur->next->next = NULL;
					cur->next->vec_pos = rand() % 2;
				}
				cube_pos += cur->vec_pos*pow(2,d-1 -j);
			}
		}
		if(cube[cube_pos] == NULL){
			cube[cube_pos] = malloc(sizeof(struct list_node));
			cube[cube_pos]->next = NULL;
			cube[cube_pos]->vec_pos = i;
		}else{
			cur = cube[cube_pos];
			while(cur->next!=NULL){
				cur = cur->next;
			}
			cur->next = malloc(sizeof(struct list_node));
			cur->next->next = NULL;
			cur->next->vec_pos = i;
		}
	}
}

int cube_search(unsigned int *g_quer, struct list_node ***f, struct list_node **cube, struct vec *vectors, struct vec query, int *distanceCube, int vec_sum, int coords, int d, int probes){
	int i, j, hash_pos, vec_pos, min, min_pos, dist, *cube_pos, *binary_string;
	struct list_node *cur;

	binary_string = malloc(d*sizeof(int));
	cube_pos = malloc(probes*sizeof(int));

	srand(time(0));
	for(j=0; j<d; j++){
		hash_pos = g_quer[j] % 4999;
		if(f[j][hash_pos ] == NULL){
			binary_string[j] = rand() % 2;
		}else{
			cur = f[j][hash_pos];
			while(cur->next!=NULL && cur->g!=g_quer[j]){
				cur = cur->next;
			}
			if(cur->g != g_quer[j]){
				binary_string[j] = rand() % 2;
			}else{
				binary_string[j] = cur->vec_pos;
			}
		}
	}
	min = 1000000;
	min_pos = -1;
	i=0;
	edges(binary_string, cube_pos, probes, d);
	for(i=0; i<probes; i++){
		if(cube[cube_pos[i]] != NULL){
			cur = cube[cube_pos[i]];
			while(cur!=NULL){
				vec_pos = cur->vec_pos;
				dist=0;					// Metrame tin manhattan distance
				for(j=0; j<coords; j++){
					dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
				}
				if(dist<min){			// Apothikeuoume to mikrotero
					min_pos=vec_pos;
					min=dist;
				}
				dist=0;
				cur = cur->next;
			}
		}
	}
	*distanceCube = min;
	return min_pos;
}
