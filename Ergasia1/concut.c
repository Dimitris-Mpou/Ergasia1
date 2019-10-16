#include <stdlib.h>

int concut(struct h_func *z, int k){
	int i, g=0;
	for(i=0; i<k; i++){
		g+= z->h[k].h_sum << (32 - 8*(i+1));								
	} 
	
	return g;
}
