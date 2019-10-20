#include <stdlib.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

void lsh_train(struct vec *vectors, struct h_func **h, int *m_factors, unsigned int **g, int vec_sum, int coords, int M, int k, int L, int w){
	int i, j, z, t, hash_pos, *a;
	float f;

	a = malloc(coords*sizeof(int));
	for(i=0; i<vec_sum; i++){
		for(z=0; z<L; z++){
			for(t=0; t<k; t++){							
				h[z][t].h_sum = 0;
				for(j=0; j<coords; j++){	
					f = (float) (vectors[i].coord[j] - h[z][t].s[j]) / w;			//Briskoume kathe a[j]
					a[j] = floor(f) + 2;						//Efarmozoume to floor kai ta kanoume thetika
					h[z][t].h_sum += (a[j] % M * m_factors[j]) % M; 				//Kanoume mod se kathe paragonta kai athroizoume
				}
				h[z][t].h_sum = h[z][t].h_sum % M;			//Kanoume mod kai so oloklhro to athroisma
			}
			g[i][z] = concut(h[z], k);
		}
	}
}

void lsh_search(struct vec query, struct h_func **h, int *m_factors, unsigned int *g, int coords, int M, int k, int L, int w){
	int i, j, t, *a;
	float f;


	a = malloc(coords*sizeof(int));
	for(i=0; i<L; i++){			// Efarmozoume tin idia diadikasia gia to query
		for(t=0; t<k; t++){								
			h[z][t].h_sum = 0;
			for(j=0; j<coords; j++){
				f = (float) (query.coord[j] - h[i][t].s[j]) / w;
				a[j]=floor(f) + 2;
				h[i][t].h_sum += (a[j] % M * m_factors[j]) % M;
			}
			h[i][t].h_sum = h[i][t].h_sum % M;
		}
		g[i] = concut(h[i], k);
	}
}
