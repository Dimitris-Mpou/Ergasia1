#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>		//////

void lsh_train(struct vec *vectors, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int M, int k, int L, int w, int TableSize){
	int i, j, z, t, hash_pos, *a;
	unsigned int g;
	float f;

	a = malloc(coords*sizeof(int));
	for(i=0; i<vec_sum; i++){
		for(z=0; z<L; z++){
			for(t=0; t<k; t++){								
				h[z][t].h_sum = 0;
				for(j=0; j<coords; j++){
					f = (float) (vectors[i].coord[j] - h[z][t].s[j]) / w;			//Briskoume kathe a[j]
					a[j]=floor(f) + 2;						//Efarmozoume to floor kai ta kanoume thetika
					h[z][t].h_sum += (a[j] % M * m_factors[j]) % M; 				//Kanoume mod se kathe paragonta kai athroizoume
				}
				h[z][t].h_sum = h[z][t].h_sum % M;			//Kanoume mod kai so oloklhro to athroisma
			}
			g = concat(h[z], k);
			hash_pos = g % (TableSize);
			hash(HashTables[z], hash_pos, g, i);
		}
	}
}

void lsh_search(struct vec *vectors, struct vec query, int center_pos, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int M, int k, int L, int w, int TableSize, int range){
	int i, j, z, t, hash_pos, *a, min, min_pos, vec_pos, dist;
	unsigned int g;
	float f;
	struct list_node *cur;


	a = malloc(coords*sizeof(int));
	min=10000000;
	min_pos=-1;
	for(z=0; z<L; z++){			// Efarmozoume tin idia diadikasia gia to query
		for(t=0; t<k; t++){								
			h[z][t].h_sum = 0;
			for(j=0; j<coords; j++){
				f = (float) (query.coord[j] - h[z][t].s[j]) / w;
				a[j]=floor(f) + 2;
				h[z][t].h_sum += (a[j] % M * m_factors[j]) % M;
			}
			h[z][t].h_sum = h[z][t].h_sum % M;
		}
		g = concat(h[z], k);
		hash_pos = g % (TableSize);			// Molis antistoixithei se bucket

		if(HashTables[z][hash_pos]!=NULL){	// An to bucket den einai adeio
			cur = HashTables[z][hash_pos];
			while(cur!=NULL){				// Trexoume olo to bucket
				//if(cur->g == g){				// Kai an ta dianusmata tou bucket exoun idio g me to query
				vec_pos = cur->vec_pos;
				printf("1\n");
				if(vectors[vec_pos].isMedoid == 0){
					printf("2\n");
					vectors[vec_pos].nearest = center_pos;
				}
				else if(vectors[vec_pos].isMedoid == 1){
					printf("3\n");
					cur = HashTables[z][hash_pos];
					assign(vectors, cur, query, vec_pos, center_pos, range, coords);
					printf("4\n");
					break;
				}
				cur=cur->next;
			}
		}
		
	}
}

void assign(struct vec *vectors, struct list_node *cur, struct vec query, int vec_pos, int center_pos, int range, int coords){
	int j;
	double dist;

	while(cur!=NULL){				// Trexoume olo to bucket
		vec_pos = cur->vec_pos;
		printf("3.1\n");
		if(vectors[vec_pos].isMedoid == 0){
			printf("3.2\n");
			dist=0;					// Metrame tin manhattan distance
			for(j=0; j<coords; j++){
				dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
			}
			if(dist < range){			// Kanoume assign ta shmeia pou einai mesa sto range
				vectors[vec_pos].nearest = center_pos;
			}
		}
		else if(vectors[vec_pos].isMedoid == 1){
			printf("3.3\n");
			assign(vectors, cur, query, vec_pos, center_pos, range, coords);
			break;
		}
		cur=cur->next;
	}
}
