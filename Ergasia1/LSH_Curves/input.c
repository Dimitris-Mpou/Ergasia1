#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int count_curves(char path[256]){
	int curves_sum;
	char ch;
	FILE *fp;

	fp = fopen(path,"r");
	curves_sum=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa curves exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			curves_sum++;
		}
	/*	}else if((ch==' ') && ((*vec_sum)==0)){
			(*coords)++;			// Metrame poses suntentagmenes exei to 1o dianusma (toses tha exoun ola)
		}*/
	}
	//(*coords)--;					// Exoume metrisei kai to id tou dianusmatos san suntetagmeni opote to afairoume

	fclose(fp);
	return curves_sum;
}


void count_points (char path[256], struct curve *curves){
	int i, z;
	char ch, *num;
	FILE *fp;
	num = malloc(10*sizeof(char));
	fp = fopen(path,"r");
	i=0;
	z=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa curves exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}
		else if(ch=='\t'){				//Apothikeuoume to plithos twn suntetagmenwn gia kathe curve
			z=0;
			ch = fgetc(fp);
			while(ch != '\t'){
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';	
			curves[i].noPoints = atoi(num);
			ch = fgetc(fp);
		}
		else if(ch=='\n'){
			i++;
		}
	} 
	fclose(fp);
}


void save_input(char path[256], struct curve *curves){
	int i, j, z;
	char ch, *num;
	FILE *fp;

	num =malloc(25*sizeof(char));	// Ara oi suntetagmenes einai mexri 9psifioi arithmoi
	fp = fopen(path,"r");			// Ksana anoigoume to arxeio wste autoi ti fora na apothikeusoume ta dianusmata
	z=0;
	j=0;
	i=0;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='('){
			ch = fgetc(fp);
			z=0;
			while(ch != ','){
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			curves[i].points[j].x = atof(num);
			ch = fgetc(fp);
			ch = fgetc(fp);
			z=0;
			while(ch != ')'){
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			curves[i].points[j].y = atof(num);
			j++;
				
		}else if(ch=='\n'){
			i++;
			j=0;

		}
	}
	fclose(fp);
}
