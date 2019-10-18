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
					f = (float) (vectors[i].coord[j] - h[z][t].s[j]) / w;			//Briskw kathe a[j]
					a[j]=floor(f) + 2;							//Efarmozw to floor kai ta kanw thetika
					h[z][t].h_sum += (a[j] % M * m_factors[j]) % M; 		//Kanw mod se kathe paragonta kai athroizw, (a*b) mod m = [(a 															mod m)*(b mod m)] mod m
				}
				h[z][t].h_sum = h[z][t].h_sum % M;						//Kanw mod kai so oloklhro to athroisma
			}
			g = concut(h[z], k);
			hash_pos = g % (TableSize);
			hash(HashTables[z], hash_pos, g, i);
		}
	}
}

int lsh_search(struct vec *vectors, struct vec query, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int M, int k, int L, int w, int TableSize){
	int i, j, z, t, hash_pos, *a, min, min_pos, vec_pos, dist;
	unsigned int g;
	float f;
	struct list_node *cur;


	a = malloc(coords*sizeof(int));
	min=10000000;
	min_pos=-1;
	for(z=0; z<L; z++){
		for(t=0; t<k; t++){								
			h[z][t].h_sum = 0;
			for(j=0; j<coords; j++){
				f = (float) (query.coord[j] - h[z][t].s[j]) / w;			//Briskw kathe a[j]
				a[j]=floor(f) + 2;							//Efarmozw to floor kai ta kanw thetika
				h[z][t].h_sum += (a[j] % M * m_factors[j]) % M;	  //Kanw mod se kathe paragonta kai athroizw, (a*b) mod m = [(a mod m)*(b mod m)] mod m
			}
			h[z][t].h_sum = h[z][t].h_sum % M;						//Kanw mod kai so oloklhro to athroisma
		}
		g = concut(h[z], k);
		hash_pos = g % (TableSize);
		if(HashTables[z][hash_pos]!=NULL){
			cur=HashTables[z][hash_pos];
			while(cur!=NULL){
				if(cur->g==g){
					vec_pos=cur->vec_pos;
					dist=0;
					for(j=0; j<coords; j++){
						dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
					}
					if(dist<min){
						min_pos=vec_pos;
						min=dist;
					}
					dist=0;
				}
				cur=cur->next;
			}
		}
		
	}
	return min_pos;
}
