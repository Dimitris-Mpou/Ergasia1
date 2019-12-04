#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main(int argc, char* argv[]){
	int i, j, z, vec_sum, coords, k, L, k_lsh, w, m, M, *m_factors, curves_sum, max_points, grids;
	char input[256], conf[256], output[256], ch;
	struct vec *vectors, *centers;
	struct curve *curves;
	struct h_func **h; 
	struct list_node ***HashTables;
	
	/*
	if(argc==9){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(conf, argv[4]);
		strcpy(output, argv[6]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio					
		printf("Give the path to the input file:\n");
		scanf("%s", input);
		printf("Give the path to the conf file:\n");
		scanf("%s", conf);
		printf("Give the path to the output file:\n");
		scanf("%s", output);
		strcpy(output, "output");
	}
	*/
	/******* Read conf file *******/
	strcpy(conf, "cluster.conf");
	configuration(conf, &k, &grids, &L, &k_lsh);
	
	//// Dokimastika print ////
	printf("k_clusters: %d\t", k);
	printf("grids: %d\t", grids);
	printf("L: %d\t", L);
	printf("k_lsh: %d\n", k_lsh);
	//////////////////////////////
	
	
	strcpy(input, "Ex2_Datasets/DataVectors_5_500x100.csv");
	strcpy(input, "Ex2_Datasets/DataVectors_5_1000x500.csv");
	//strcpy(input, "Εργασία 2 - Καμπύλες/input_projection6.csv");
	
	FILE *fp;
	fp = fopen(input,"r");
	ch = fgetc(fp);

	if(ch == 'v'){
		/***** Input dianusmatwn *****/
		count_vecs(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
		vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume

		for(i=0; i<vec_sum; i++){
			vectors[i].coord = malloc(coords*sizeof(double));
			vectors[i].isMedoid = 0;
			vectors[i].nearest = -1;
		}
		save_vecs(input, vectors);

		printf("Vectors= %d\tCoordinates = %d\n", vec_sum, coords);
	}
	else if(ch == 'c'){
		/***** Input kampulwn *****/
		curves_sum = count_curves(input);							// Metrame to plithos twn curves
		curves = malloc(curves_sum*sizeof(struct curve));
		
		max_points = save_curves(input, curves, curves_sum);					// Metrame to plithos twn suntetagmenwn kathe curve
		
		///////////////////// Dokimastika print ///////////////////////
		printf("Curves=%d  Max_points=%d\n", curves_sum, max_points);	
		for(i=0; i<5; i++){
			printf("%d \t %d\t", curves[i].id, curves[i].noPoints);
			for(j=0; j<curves[i].noPoints; j++){
				printf("(%.20f, %.20f) ", curves[i].points[j].x, curves[i].points[j].y);
			}
			printf("\n");
		}
		printf("%d\n", curves[0].noPoints);
		printf("%d\n", curves[1599].noPoints);
		printf("%d\n", curves[2315].noPoints);				//Edw tha eprepe na vgazei seg??
		/////////////////////////////////////
	}
	
	
	/****** Initialize ***********/
	//k = 100;
	centers = malloc(k*sizeof(struct vec));
	for(i=0; i<k; i++)
		centers[i].coord = malloc(coords*sizeof(double));
	random_selection(vectors, vec_sum, k);
//	k_means_plus_plus(vectors, vec_sum, k, coords);
	
	int c=0;
	for(i=0; i<vec_sum; i++){				// isMedoid, nearest??
		if (vectors[i].isMedoid == 1){
			for(j=0; j<coords; j++){
				centers[c].coord[j] = vectors[i].coord[j];
			}
			c++;
		}
	}

	/****** Assignment ***********/

	/*	Lsh Initialize	*/

	L = 5;
	k_lsh = 4;
	w = 4500;	
	m = 5;
	M = pow(2, 32/k_lsh);

	h = malloc(L*sizeof(struct h_func *));						// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){	
		h[i] = malloc(k_lsh*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k_lsh; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));												// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k_lsh; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = w*(rand() / (RAND_MAX +1.0));
			}
		}
	}
	HashTables = malloc(L*sizeof(struct list_node **));			// Kanoume malloc gia tous L Hashtables
	for(i=0; i<L; i++){
		HashTables[i] = malloc(vec_sum/8*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){											// Ola ta buckets twn hashtables dixnoun NULL
		for(j=0; j<vec_sum/8; j++){
			HashTables[i][j] = NULL;
		}
	}
	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k_lsh, L, w, vec_sum/8);		// Ekteloume to lsh gia to input data
	
	LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k);
//	Lloyds_assignment(vectors, centers, vec_sum, coords, k);

	/****** Update ***********/

//	PAM(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k);
	PAMean(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k);

	return 0;
}
