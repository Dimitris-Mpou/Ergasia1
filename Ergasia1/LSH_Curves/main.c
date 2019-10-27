#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, p, curves_sum, max_points, **grids, ****grid_curves, k_vec, L_grid, d_greek, **t, grid_length, count;
	char input[256], query[256], output[256];
	struct curve *curves;
	struct vec **vectors;
	
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
	printf("Curves = %d\n", curves_sum);
	for(i=0; i<curves_sum; i++){
		//printf("%d %d\n", i, curves[i].noPoints);
		curves[i].points = malloc(curves[i].noPoints*sizeof(struct point));
	}	
	save_input(input, curves);

//	d_greek = count_d(curves, curves_sum);		d = 0.002212, to pollaplasiazoume epi 1000
	d_greek=2;
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
			t[i][j] = 2 * (rand() / (RAND_MAX +1.0));
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

	vectors = malloc(L_grid*sizeof(struct vec *)); // Seg edw mesa
	for(i=0; i<curves_sum; i++){
		vectors[i] = malloc(curves_sum*sizeof(struct vec));
		for(j=0; j<curves_sum; j++){
			vectors[i][j].coord = malloc(max_points*2*sizeof(int));
			vectors[i][j].id = curves[j].id;
			count = 0;
			for(z=0; z<curves[j].noPoints * 2; z++){
				vectors[i][j].coord[count] = grid_curves[i][j][z][1];
				vectors[i][j].coord[count+1] = grid_curves[i][j][z][2];
				count +=2;
			}
			for(z; z<max_points*2; z+=2){
				vectors[i][j].coord[z] = 0;
				vectors[i][j].coord[z+1] = 0;
			}
		}
	}
	printf("Here");

	printf("%d. (", vectors[0][0].id);
	for(i=0; i<max_points; i++){
		printf("%d, ", vectors[0][0].coord[i]);		
	}
	printf(")\n");
	

/*	for(i=0; i<1; i++){
		for(j=0; j<curves[i].noPoints; j++){
			printf("%.16f, %.16f\n", curves[i].points[j].x, curves[i].points[j].y);
		}
	}
*/
	
	return 0;
}
