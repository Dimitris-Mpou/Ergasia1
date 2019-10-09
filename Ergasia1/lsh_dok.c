#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main (int argc, char *argv[]){
	int i, vec_sum, coords;
	char ch, *num;
	struct vec *vectors;
	FILE *fp;

	vectors=malloc(sizeof(struct vec));
	num =malloc(5*sizeof(char));

	fp = fopen("/siftsmall/input_small_id","r");		// ????
	coords=0;
	vec_sum=0;
	while(1){														// Sarwnw to arxeio metrwntas posa dianusmata exei
		ch = fgetc(fp);
		printf("Here\n");
		if(ch==EOF){
			vec_sum++;
			break;
		}else if(ch=='\n'){
			vec_sum++;
			printf("%d\n", vec_sum);
		}else if((ch==' ') && (vec_sum==0)){
			coords++;												// Metraw poses suntentagmenes exei to 1o dianusma (toses tha exoun ola)
		}
	}

	fclose(fp);
/*	fp = fopen("/siftsmall/input_small_id","r");
	while(0){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			
		}else if(ch==' '){
			i=0;
		}else{
			num[i]=ch;
			num[i++]='\n';
		}	
	}
*/
	printf("Vectors = %d\tCoordinates = %d\n", vec_sum, coords);

	return 0;
}
