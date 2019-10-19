#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, d, w, M_Cube, probes, vec_sum, quer_sum, coords, m, M, *m_factors, sum, *search_results, *cube_results, *distanceTrue, *distanceCube;
	unsigned int **g;
	char ch, *num, input[256], query[256], output[256];
	float r, *tCube, *tTrue;
	clock_t start, stop;
	struct vec *vectors, *queries;
	struct h_func **h;
	struct list_node ***f;
	FILE *fp;	

	if(argc==13){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(query, argv[4]);
		d = atoi(argv[6]);
		M_Cube = atoi(argv[8]);
		probes = atoi(argv[10]);
		strcpy(output, argv[12]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio
		d = 3;
		M_Cube = 10;
		probes = 2;								
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
	k=4;

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);
	vectors = malloc(vec_sum*sizeof(struct vec));					// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(int));
	}
	save_input(input, vectors);							// Apothikeuoume ta dianusmata

	count_input(query, &quer_sum, &coords);						// Metrame to plithos twn queries
	printf("Queries = %d\tCoordinates = %d\n", quer_sum, coords);
	queries = malloc(quer_sum*sizeof(struct vec));					// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<quer_sum; i++){
		queries[i].coord = malloc(coords*sizeof(int));
	}
	save_input(query, queries);							// Apothikeuoume ta queries

	search_results = malloc(quer_sum*sizeof(int));
	cube_results = malloc(quer_sum*sizeof(int));
	distanceTrue = malloc(quer_sum*sizeof(int));
	distanceCube = malloc(quer_sum*sizeof(int));
	tCube = malloc(quer_sum*sizeof(float));
	tTrue = malloc(quer_sum*sizeof(float));
	g = malloc(vec_sum*sizeof(unsigned int *));
	for(i=0; i<vec_sum; i++){
		g[i] = malloc(d*sizeof(unsigned int));
	}
	f = malloc(d*sizeof(struct list_node **));
	for(i=0; i<d; i++){
		f[i] = malloc(4999*sizeof(struct list_node *));
	}

	for(i=0; i<d; i++){
		for(j=0; j<4999; j++){
			f[i][j] = NULL;
		}
	}

	for(i=0; i<quer_sum; i++){
		start = clock();
		search_results[i] = query_knn(vec_sum, coords, vectors, queries[i], &distanceTrue[i]);	// Kwdikas exantlitikis anazitisis
		stop = clock();
		tTrue[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}

//	r = average_dist(vec_sum, coords, vectors);					// Kwdikas gia ton upologismo tou r wste na thesoume w = 4*r
//	printf("r = %f\n", r);
	w = 4500;

	h = malloc(d*sizeof(struct h_func *));				// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<d; i++){	
		h[i] = malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<d; i++){
		for(j=0; j<k; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));								// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<d; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = rand()%w;
			}
		}
	}
	
	m = 5;											// Ekxwroume times sta m, M
	M = pow(2, 32/k);

	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	lsh(vectors, h, m_factors, g, vec_sum, coords, M, k, d, w);			// Ekteloume to lsh gia to input data
	cube_train(g, f, vec_sum, d);

	for(i=0; i<quer_sum; i++){									// Ekteloume lsh gia ta queries
		start = clock();
//		cube_results[i] = cube_search();
		cube_results[i]=i;
		stop = clock();
		tCube[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}

	write_output(output, quer_sum, queries, vectors, cube_results, distanceCube, distanceTrue, tCube, tTrue);

	sum=0;
	//printf("Actual Result\tCube Result\tdistanceTrue\tdistanceLSH\n\n");
	for(i=0; i<quer_sum; i++){
//		printf("%d\t\t%d\t\t%d\t\t%d\n", search_results[i], cube_results[i], distanceTrue[i], distanceCube[i]);
		if(search_results[i]==cube_results[i]){sum++;}
	}
	printf("Score: %d / %d\n", sum, quer_sum);

	return 0;
}
