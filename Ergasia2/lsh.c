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

void lsh_search(struct vec *vectors, struct vec *centers, int center_pos, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int M, int k, int L, int w, int TableSize, int k_clusters){
	int i, j, z, t, hash_pos, *a, vec_pos, dist;
	double min_dist;
	unsigned int g;
	float f;
	struct list_node *cur;

	for(i=0; i<vec_sum; i++){
		vectors[i].nearest = -1;	
	}

	a = malloc(coords*sizeof(int));

	for(i=0; i<k_clusters; i++){
		for(z=0; z<L; z++){			// Efarmozoume tin idia diadikasia gia to query-center
			for(t=0; t<k; t++){							
				h[z][t].h_sum = 0;
				for(j=0; j<coords; j++){
					f = (float) (centers[i].coord[j] - h[z][t].s[j]) / w;
					a[j] = floor(f) + 2;
					h[z][t].h_sum += (a[j] % M * m_factors[j]) % M;
				}
				h[z][t].h_sum = h[z][t].h_sum % M;
			}

			g = concat(h[z], k);
			hash_pos = g % (TableSize);			// Molis antistoixithei se bucket
			if(HashTables[z][hash_pos]!=NULL){	// An to bucket den einai adeio
				cur = HashTables[z][hash_pos];
				while(cur!=NULL){				// Trexoume olo to bucket
					if(cur->g == g){			// Kai an ta dianusmata tou bucket exoun idio g me to query-center
						vec_pos = cur->vec_pos;
						if(vectors[vec_pos].nearest == -1){	// An einai to prwto kentro pou zitaei auto to vector
							vectors[vec_pos].nearest = i;
						}else{
							if(manhattan_distance(vectors[vec_pos], centers[i], coords) < manhattan_distance(vectors[vec_pos], centers[vectors[vec_pos].nearest], coords))
								vectors[vec_pos].nearest = i;	// Alliws an auto to kentro einai pio konta ap ta proigoumena pou eixan zitisei auto to dianusma
						}
					}
					cur = cur->next;
				}
			}
		}
	}
	for(i=0; i<vec_sum; i++){
		if(vectors[vec_pos].nearest == -1){	// Gia osa dianusmata den epese center sto idio bucket
			min_dist = 10000000.0;		
			for(j=0; j<k_clusters; j++){
				dist = manhattan_distance(vectors[i], centers[j], coords);
				if(dist  < min_dist ){
					vectors[i].nearest = j;
					min_dist = dist;
				}
			}
		}
	}
}
