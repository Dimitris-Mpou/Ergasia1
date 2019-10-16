#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, t, L, w, flag, vec_sum, coords, *a, m, M, *m_power, g, final, TableSize, sum;
	char ch, *num, path[256];
	float f;
	struct vec *vectors;
	struct h_func **h; 
	struct list_node ***HashTables, *cur;
	FILE *fp;

	k=4;
	L=5;
	w=4*880;														// Na kanoume dokimes!!!!
	//printf("Give the path to the data set:\n");
	//scanf("%s", path);
	strcpy(path, "siftsmall/input_small_id");

	count_input(path, &vec_sum, &coords);
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors=malloc(vec_sum*sizeof(struct vec));						// Kanw malloc gia na apothikeusw ta dianusmata
	for(i=0; i<vec_sum; i++){
		vectors[i].coord=malloc(coords*sizeof(int));
	}
	save_input(path, &vectors);
	

	printf("%f\n", average_dist(vec_sum, coords, &vectors));		// Aplos kwdikas anazitisis gia ton evresi tis mesis apostasis apo ton plisiestero geitona
	

	h=malloc(L*sizeof(struct h_func *));							// Ftiaxnw tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){
		h[i]=malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s=malloc(coords*sizeof(int));
		}
	}
	srand(time(0));													// Dinw tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z]=rand()%w;
			}
		}
	}
	a=malloc(coords*sizeof(int));

	/* Gia tin dimiourgia twn hashtables : */
	
	TableSize=vec_sum/8;
	HashTables=malloc(L*sizeof(struct list_node **));
	for(i=0; i<L; i++){
		HashTables[i]=malloc(TableSize*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){
		for(j=0; j<TableSize; j++){
			HashTables[i][j]=NULL;
		}
	}
	
	m = 5;
	M = 128;
	m_power=malloc(coords*sizeof(int));
	for(j=0; j<coords; j++){
		m_power[j] = modulo_calc(m, (coords-1) - j, M);			// Ypologizw kai apothikeuw ola ta m^(coords-1)-j % M giati einai 128 ki epanaxrisopoiountai polles fores
	}

	for(i=0; i<vec_sum; i++){
		for(z=0; z<L; z++){
			for(t=0; t<k; t++){								
				h[z][t].h_sum = 0;
					for(j=0; j<coords; j++){
						f = (float) (vectors[i].coord[j] - h[z][t].s[j]) / w;			//Briskw kathe a[j], lathos!!!
						a[j]=floor(f) + 2;							//Efarmozw to floor kai ta kanw thetika
						h[z][t].h_sum += (a[j] % M * m_power[j]) % M;			//Kanw mod se kathe paragonta kai athroizw, (a*b) mod m = [(a mod m)*(b mod m)] mod m
					}
				h[z][t].h_sum = h[z][t].h_sum % M;						//Kanw mod kai so oloklhro to athroisma		
			}
			g=0;														// !!!! Prepei na paixoume me to k !!!!!
			g+=h[z][0].h_sum<<24;
			g+=h[z][1].h_sum<<16;
			g+=h[z][2].h_sum<<8;
			g+=h[z][3].h_sum;
			final = g % (TableSize);
			cur=HashTables[z][final];
			if(cur==NULL){
				HashTables[z][final]=malloc(sizeof(struct list_node));
				HashTables[z][final]->next=NULL;
				HashTables[z][final]->g=g;
				HashTables[z][final]->vec_pos=i;
			}else{
				while(cur->next!=NULL){
					cur= cur->next;
				}
				cur->next= malloc(sizeof(struct list_node));
				cur->next->g=g;
				cur->next->next=NULL;
				cur->next->vec_pos=i;
			}
		}
	}

	printf("TableSize = %d\nt = ", TableSize);
	z=0;
	sum=0;
	for(i=0; i<L; i++){
		for(j=0; j<TableSize; j++){
			cur=HashTables[i][j];
			if(cur!=NULL){
				t=1;
				while(cur->next!=NULL){
					cur=cur->next;
					t++;
				}
				printf("%d ", t);
				sum+=t;
			}else{
				z++;
			}
		}
		printf("\nsum = %d\nt =", sum);
		sum=0;
	}
	printf("\nz = %d\n", z);
	



/*	for(i=0; i<vec_sum; i++){
		printf("%d.\t", i+1);										// Emfanizw olo to arxeio
		for(j=0; j<coords; j++){
			printf("%d ", vectors[i].coord[j]);
		}
		printf("\n\n");
	}*/

	return 0;
}
