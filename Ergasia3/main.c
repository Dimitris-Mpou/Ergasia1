#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main(int argc, char* argv[]){
	int i, j, z, vec_sum, coords, c, k, L, k_lsh, w, m, M, *m_factors, curves_sum, max_points, grids, lamda;
	double  *s;
	time_t start, stop, duration;
	char input[256], conf[256], output[256], ch, vec_init, vec_asign, vec_upd;
	struct vec *vectors, *centers;
	struct curve *curves, *centers_curve, *C;
	struct h_func **h; 
	struct list_node ***HashTables;
	struct pair *traversal;
	
	/*
	if(argc==7){					// Pairnoume ta orismata
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
	}
	*/
	/******* Read conf file *******/

	//configuration(conf, &k, &grids, &L, &k_lsh);
	strcpy(input, "nn_representations.csv");
	strcpy(output, "output.txt");

	start = time(0);

	k=4;
	L=4;
	k_lsh=4;
	vec_sum = 23988;
	if(strcmp(input, "nn_representations.csv") == 0){
		coords = 128;
	}
	else if(strcmp(input, "new_representation.csv") == 0){
		coords = 64;
	}
	
	printf("vec_sum=%d  coords=%d\n", vec_sum, coords);


		/***** Input dianusmatwn *****/
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume

	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
		vectors[i].isMedoid = 0;
		vectors[i].nearest = -1;
	}

	save_vecs(input, vectors, vec_sum, coords);
	/*printf("%s\n", vectors[23987].id);
	for(i=0; i<1; i++){
		for(j=0; j<coords; j++){
			printf("%.10f\t", vectors[i].coord[j]);
		}
		printf("\n");
	}*/

	vec_init = 1;
	vec_asign = 1;
	vec_upd = 1;
		/****** Initialize ***********/
	//start = clock();
	centers = malloc(k*sizeof(struct vec));
	for(i=0; i<k; i++)
		centers[i].coord = malloc(coords*sizeof(double));

	if(vec_init == 1)
		random_selection(vectors, vec_sum, k);
	else
		k_means_plus_plus(vectors, vec_sum, k, coords);
	
	c = 0;
	for(i=0; i<vec_sum; i++){				// isMedoid, nearest??
		if (vectors[i].isMedoid == 1){
			for(j=0; j<coords; j++){
				centers[c].coord[j] = vectors[i].coord[j];
			}
			strcpy(centers[c].id, vectors[i].id);
			c++;
		}
	}
	
	for(i=0; i<k; i++){
		printf("%s\t", centers[i].id);
	}
	
		/****** Assignment ***********/
	if(vec_asign == 1){
		Lloyds_assignment(vectors, centers, vec_sum, coords, k);
	}else{
		lsh_init(&w, &m, &M, &h, &HashTables, &m_factors, vec_sum, coords, k_lsh, L);		// Kanoume ta katallila malloc kai tis arxikopoiiseis
		lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k_lsh, L, w, vec_sum/8);		// Ekteloume to lsh gia to input data
		LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);
	}

		/****** Update ***********/
	printf("7\n");
	if(vec_upd == 1){
		printf("1\n"); 
		PAM(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);
	}
	else{
		printf("2\n"); 
		PAMean(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);
		printf("3\n"); 
	}
	stop = time(0);
	duration = stop - start;
	printf("Duration=%ld\n", duration);
	for(i=0; i<k; i++){
		printf("%s\t", centers[i].id);
	}
	//stop = clock();
	//duration = (double) stop - start;
	printf("7.1\n");
	s = malloc(vec_sum*sizeof(double));
	vec_silhouette(vectors, vec_sum, coords, s);
	printf("7.2\n");
	vec_write_output(output, vectors, centers, vec_sum, k, vec_upd, s, coords, duration);
	printf("8\n");
	return 0;
}
