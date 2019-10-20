#include <stdlib.h>
#include <time.h>
#include "headers.h"

void cube_train(struct projection *p, int vec_sum, int d){
	int i, z, j, flag;

	for(i=0; i<vec_sum; i++){
		for(z=0; z<d; z++){
			flag = 0;
			for(j=0; j<z; j++){				//Elegxoume an uparxei hdh f(g) gia to antistoixo g
				if(p[i].g[z] == p[i].g[j]){
					p[i].f[z] = p[i].f[j];
					flag = 1;
					break;
				}
			}
			if (flag == 0){					//An den uparxei dmhiourgoume tuxaio (0,1)
				srand(time(0));		
				p[i].f[z] = rand() % 2;
			}
		}
	}
}
