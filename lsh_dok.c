#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	int i;
	char ch, *num;
	FILE *fp;

	num =malloc(5*sizeof(char));

	fp = fopen("/siftsmall/input_small_id","r");
	while(0){														// Sarwnw to arxeio metrwntas posa documents exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			
		}	
	}

//	Dokimi
	num[0]='1';
	num[1]='9';
	num[2]='0';
	num[3]='8';
	num[4]='\n';
	printf("%d\n", atoi(num));

	return 0;
}
