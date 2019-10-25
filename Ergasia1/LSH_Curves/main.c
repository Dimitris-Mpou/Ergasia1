#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include "functions.h"

int main (int argc, char *argv[]){
	
	int i, j, curves_sum;
	char path[256];
	struct curve *curves;
	
	
	strcpy(path, "trajectories_dataset");
	
	curves_sum = count_curves(path);							// Metrame to plithos twn curves

	curves = malloc(curves_sum*sizeof(struct curve));
	count_points(path, curves);						// Metrame to plithos twn suntetagmenwn kathe curve
	printf("Curves = %d\n", curves_sum);
	for(i=0; i<curves_sum; i++){
		//printf("%d %d\n", i, curves[i].noPoints);
		curves[i].points = malloc(curves[i].noPoints*sizeof(struct point));
	}
				
	save_input(path, curves);
	for(i=0; i<1; i++){
		for(j=0; j<curves[i].noPoints; j++){
			printf("%.16f, %.16f\n", curves[i].points[j].x, curves[i].points[j].y);
		}
	}
	return 0;
}
