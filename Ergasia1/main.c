#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, t, L, w, vec_sum, quer_sum, coords, m, M, *m_factors, TableSize, sum, *search_results, *lsh_results, *distanceTrue, *distanceLSH;
	unsigned int g;
	char ch, *num, input[256], query[256], output[256];
	float r, *tLSH, *tTrue;
	clock_t start, stop;
	struct vec *vectors, *queries;
	struct h_func **h; 
	struct list_node ***HashTables, *cur;
	FILE *fp;	

	if(argc==11){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(query, argv[4]);
		k = atoi(argv[6]);
		L = atoi(argv[8]);
		strcpy(output, argv[10]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio
		k = 4;
		L = 5;								
		//printf("k = 4\tL = 5\nGive the path to the input file:\n");
		//scanf("%s", input);
		strcpy(input, "siftsmall/input_small_id");
		//printf("Give the path to the query file:\n");
		//scanf("%s", query);
		strcpy(query, "siftsmall/query_small_id");
		//printf("Give the path to the output file:\n");
		//scanf("%s", output);
		strcpy(output, "output");
	}

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(int));
	}
	save_input(input, vectors);									// Apothikeuoume ta dianusmata

	count_input(query, &quer_sum, &coords);						// Metrame to plithos twn queries
	printf("Queries = %d\tCoordinates = %d\n", quer_sum, coords);
	queries = malloc(quer_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		queries[i].coord = malloc(coords*sizeof(int));
	}
	save_input(query, queries);									// Apothikeuoume ta queries

	search_results = malloc(quer_sum*sizeof(int));
	lsh_results = malloc(quer_sum*sizeof(int));
	distanceTrue = malloc(quer_sum*sizeof(int));
	distanceLSH = malloc(quer_sum*sizeof(int));
	tLSH = malloc(quer_sum*sizeof(float));
	tTrue = malloc(quer_sum*sizeof(float));

	for(i=0; i<quer_sum; i++){
		start = clock();
		search_results[i] = query_knn(vec_sum, coords, vectors, queries[i], &distanceTrue[i]);	// Kwdikas exantlitikis anazitisis
		stop = clock();
		tTrue[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}

	r = average_dist(vec_sum, coords, vectors);					// Kwdikas gia ton upologismo tou r wste na thesoume w = 4*r
	printf("r = %f\n", r);
	w = 4000;

	h = malloc(L*sizeof(struct h_func *));						// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){	
		h[i] = malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));												// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = rand()%w;
			}
		}
	}
	
	TableSize = vec_sum/8;										// Kanoume malloc gia tous L Hashtables
	HashTables = malloc(L*sizeof(struct list_node **));
	for(i=0; i<L; i++){
		HashTables[i] = malloc(TableSize*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){											// Ola ta buckets twn hashtables dixnoun NULL
		for(j=0; j<TableSize; j++){
			HashTables[i][j] = NULL;
		}
	}
	
	m = 5;														// Ekxwroume times sta m, M
	M = pow(2, 32/k);

	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize);	// Ekteloume to lsh gia to input data
	for(i=0; i<quer_sum; i++){									// Ekteloume lsh gia ta queries
		start = clock();
		lsh_results[i] = lsh_search(vectors, queries[i], h, HashTables, m_factors, &distanceLSH[i], vec_sum, coords, M, k, L, w, TableSize);
		stop = clock();
		tLSH[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}

	write_output(output, quer_sum, queries, vectors, lsh_results, distanceLSH, distanceTrue, tLSH, tTrue);


	sum=0;
//	printf("Actual Result\tLSH Result\tdistanceTrue\tdistanceLSH\n\n");
	for(i=0; i<quer_sum; i++){
//		printf("%d\t\t%d\t\t%d\t\t%d\n", search_results[i], lsh_results[i], distanceTrue[i], distanceLSH[i]);
		if(search_results[i]==lsh_results[i]){sum++;}
	}
	printf("Score: %d / %d\n", sum, quer_sum);


/*	for(i=0; i<vec_sum; i++){
		printf("%d.\t", i+1);						// Emfanizw olo to arxeio
		for(j=0; j<coords; j++){
			printf("%d ", vectors[i].coord[j]);
		}
		printf("\n\n");
	}
*/
	return 0;
}
