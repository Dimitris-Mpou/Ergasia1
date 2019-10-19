#include <stdlib.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

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
			g = concut(h[z], k);
			hash_pos = g % (TableSize);
			hash(HashTables[z], hash_pos, g, i);
		}
	}
}

int lsh_search(struct vec *vectors, struct vec query, struct h_func **h, struct list_node ***HashTables, int *m_factors, int *min_distance, int vec_sum, int coords, int M, int k, int L, int w, int TableSize){
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
		g = concut(h[z], k);
		hash_pos = g % (TableSize);			// Molis antistoixithei se bucket
		if(HashTables[z][hash_pos]!=NULL){	// An to bucket den einai adeio
			cur=HashTables[z][hash_pos];
			while(cur!=NULL){				// Trexoume olo to bucket
				if(cur->g==g){				// Kai an ta dianusmata tou bucket exoun idio g me to query
					vec_pos=cur->vec_pos;
					dist=0;					// Metrame tin manhattan distance
					for(j=0; j<coords; j++){
						dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
					}
					if(dist<min){			// Apothikeuoume to mikrotero
						min_pos=vec_pos;
						min=dist;
					}
					dist=0;
				}
				cur=cur->next;
			}
		}
		
	}
	*min_distance=min;
	return min_pos;							// Ki epistrefoume tin thesi tou ston pinaka vectors
}
