#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main(int argc, char* argv[]){
	int i, j, z, vec_sum, coords, c, k, L, k_lsh, w, m, M, *m_factors, curves_sum, max_points, grids, lamda;
	char input[256], conf[256], output[256], ch, vec_init, vec_asign, vec_upd;
	struct vec *vectors, *centers;
	struct curve *curves, *centers_curve;
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
	strcpy(input, "Εργασία 2 - Καμπύλες/input_projection6.csv");
//	strcpy(input, "curves_clustering/input_projection6.csv");
	
	FILE *fp;							//Elegxoume an to dataset einai gia vecs h curves
	fp = fopen(input,"r");
	ch = fgetc(fp);
	fclose(fp);

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
		vec_init = 1;
		vec_asign = 2;
		vec_upd = 2;
			/****** Initialize ***********/

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
				c++;
			}
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

		if(vec_upd == 1)
			PAM(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);
		else
			PAMean(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);

	}
	else if(ch == 'c'){
			/***** Input kampulwn *****/
		curves_sum = count_curves(input);							// Metrame to plithos twn curves
		curves = malloc(curves_sum*sizeof(struct curve));
		max_points = save_curves(input, curves, curves_sum);					// Metrame to plithos twn suntetagmenwn kathe curve
		
		printf("Curves=%d  Max_points=%d\n", curves_sum, max_points);	//// Dokimastika print 

			/****** Initialize ***********/
		
		centers_curve = malloc(k*sizeof(struct curve));
		random_selection_curve(curves, curves_sum, k);
		c=0;
		for(i=0; i<curves_sum; i++){
			if (curves[i].isMedoid == 1){
				centers_curve[c].id = curves[i].id;
				centers_curve[c].noPoints = curves[i].noPoints;
				centers_curve[c].points = malloc(curves[i].noPoints*sizeof(struct point));
				for(j=0; j<centers_curve[c].noPoints; j++){
					centers_curve[c].points[j] = curves[i].points[j];
				}
				c++;
			}
		}

			/****** Assignment ***********/

		Lloyds_assignment_curve(curves, centers_curve, curves_sum, k);
			
			/****** Update ***********/
		PAMean_curves(curves, centers_curve, curves_sum, k);

	}
	
	return 0;
}
