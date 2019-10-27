#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, p, curves_sum, max_points, **grids, ****grid_curves, k_vec, L_grid, delta, **t, grid_length, w, h, k, TableSize, vec_sum, quer_sum, *search_results, *lsh_results, *distanceTrue, *distanceLSH;
	char input[256], query[256], output[256];
	float *tLSH, *tTrue;
	clock_t start, stop;
	struct curve *curves;
	struct vec **vectors, *queries;
	
	if(argc==11){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(query, argv[4]);
		k_vec = atoi(argv[6]);
		L_grid = atoi(argv[8]);
		strcpy(output, argv[10]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio							
/*		printf("Give the path to the input file:\n");
		scanf("%s", input);
		printf("Give the path to the query file:\n");
		scanf("%s", query);
		printf("Give the path to the output file:\n");
		scanf("%s", output);	*/
		strcpy(input, "trajectories_dataset");
		k_vec = 4;
		L_grid = 4;
	}
	
	curves_sum = count_curves(input);							// Metrame to plithos twn curves
	curves = malloc(curves_sum*sizeof(struct curve));
	max_points = count_points(input, curves);					// Metrame to plithos twn suntetagmenwn kathe curve
	printf("Curves = %d max points = %d\n", curves_sum, max_points);
	for(i=0; i<curves_sum; i++){
		curves[i].points = malloc(curves[i].noPoints*sizeof(struct point));
	}	
	save_input(input, curves);

//	delta = count_d(curves, curves_sum);		d = 0.002212, to pollaplasiazoume epi 1000
	delta=2;
	grid_length = 2000;

	grids = malloc(L_grid*sizeof(int *));				// Kanoume malloc gia ta grids
	for(i=0; i<L_grid; i++){
		grids[i] = malloc(grid_length*sizeof(int));
	}
	for(i=0; i<L_grid; i++){							// Ta gemizoume
		z = -7000;
		for(j=0; j<grid_length/2; j++){
			grids[i][j] = z;
			z++;
		}
		z = 53000;
		for(j=grid_length/2; j<grid_length; j++){
			grids[i][j] = z;
			z++;
		}
	}

	srand(time(0));
	t = malloc(L_grid*sizeof(int *));					// Ypologizoume kai prosthetoume ta t
	for(i=0; i<L_grid; i++){
		t[i] = malloc(grid_length*sizeof(int));
		for(j=0; j<grid_length; j++){
			t[i][j] = delta * (rand() / (RAND_MAX +1.0));
			grids[i][j] += t[i][j];
		}
	}

	grid_curves = malloc(L_grid*sizeof(int ***));		// Kanw malloc tis kampules pou tha bgoun ap ta snap
	for(i=0; i<L_grid; i++){
		grid_curves[i] = malloc(curves_sum*sizeof(int **));
		for(j=0; j<curves_sum; j++){
			grid_curves[i][j] = malloc(curves[j].noPoints*sizeof(int *));
			for(z=0; z<curves[j].noPoints; z++){
				grid_curves[i][j][z] = malloc(2*sizeof(int));
			}
		}
	}

	snap(curves, grid_curves, grids, curves_sum, grid_length, L_grid);
	for(i=0; i<curves[0].noPoints; i++){
		printf("(%f, %f)\t(%d, %d)\n", curves[0].points[i].x, curves[0].points[i].y, grid_curves[0][0][i][0], grid_curves[0][0][i][1]);
	}

	vectors = malloc(L_grid*sizeof(struct vec *));
	for(i=0; i<L_grid; i++){
		vectors[i] = malloc(curves_sum*sizeof(struct vec));
		for(j=0; j<curves_sum; j++){
			vectors[i][j].coord = malloc(max_points*2*sizeof(int));
		}
	}
	concat_curve(vectors, curves, grid_curves, curves_sum, max_points, L_grid);


/*
	printf("%d. (", vectors[0][6].id);
	for(i=0; i<max_points; i++){
		printf("%d, ", vectors[0][6].coord[i]);		
	}
	printf(")\n");
*/
/*********	LSH	***********/
	
	quer_sum = 86;
	queries = malloc(quer_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<quer_sum; i++){
		queries[i].coord = malloc(max_points*sizeof(int));
		for(j=0; j<=max_points; j++){
			queries[i].coord[j] = vectors[curves_sum - 86 + i].coord[j]; 	// Apothikeuoume ta queries
		}
	}
				
	vec_sum = 7400;	

	search_results = malloc(quer_sum*sizeof(int));
	lsh_results = malloc(quer_sum*sizeof(int));
	distanceTrue = malloc(quer_sum*sizeof(int));
	distanceLSH = malloc(quer_sum*sizeof(int));
	tLSH = malloc(quer_sum*sizeof(float));
	tTrue = malloc(quer_sum*sizeof(float));

	for(i=0; i<quer_sum; i++){
		start = clock();
		search_results[i] = query_knn(vec_sum, max_points, vectors, queries[i], &distanceTrue[i]);	// Kwdikas exantlitikis anazitisis
		stop = clock();
		tTrue[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}
	w = 4500;

	lsh(vectors, queries, curves, vec_sum, quer_sum, max_points, k, L_grid, w, lsh_results, distanceLSH, tLSH);
	write_output(output, quer_sum, queries, vectors, lsh_results, distanceLSH, distanceTrue, tLSH, tTrue);	
	return 0;
}
