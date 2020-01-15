#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void configuration(char path[256], int *k_clusters, int *grids, int *L, int *k_lsh){
	char ch, *num;
	int line, z;
	FILE *fp;
	fp = fopen(path,"r");
	num = malloc(5*sizeof(char));

	line = 1;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}
		else if(ch==':'){
			ch = fgetc(fp); 		//Diavazei to keno
			ch = fgetc(fp); 
			z=0;
			while(ch != '\n'){		//Apothikeuoume to id tou kathe curve
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';
			if(line == 1){	
				(*k_clusters) = atoi(num);
			}
			else if(line == 2){	
				(*grids) = atoi(num);
			}
			else if(line == 3){	
				(*L) = atoi(num);
			}
			else if(line == 4){	
				(*k_lsh) = atoi(num);
			}
			line++;
		}
	}		
		
}

void save_vecs(char path[256], struct vec *vectors){
	int i, j, z, vec_sum, coords;
	char ch, *num;
	FILE *fp;

	num =malloc(30*sizeof(char));
	fp = fopen(path,"r");			// Anoigoume to arxeio wste auti ti fora na apothikeusoume ta dianusmata
	
	vec_sum = 23988;
	coords = 128;
	z=0;
	j=0;
	i=0;
	//printf("%d\t", i); 
	
	for(i=0; i<vec_sum; i++){
		ch = fgetc(fp);
		while(ch != ','){			//prospername thn prwth sthlh			
			ch = fgetc(fp);
		}
		
		for(j=0; j<coords; j++){
			z=0;
			ch =  fgetc(fp);
			while(ch != ',' && ch != '\n'){
				num[z] = ch;
				z++;			
				ch = fgetc(fp);
			}
			num[z] = '\0';
			vectors[i].coord[j] = atof(num);
		
		}

	}

	fclose(fp);
}
