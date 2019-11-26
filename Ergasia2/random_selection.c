#include <time.h>
#include <stdlib.h>
#include "structs.h"

void random_selection(struct vec *vectors, int vec_sum, int k){
	int i, c;

	srand(time(0));							
	for(i=0; i<k; i++){
		do{							//Etsi wste na mh einai hdh medoid
			c = vec_sum*(rand() / (RAND_MAX +1.0));
		}
		while(vectors[c].isMedoid == 1);
		vectors[c].isMedoid = 1;
	}
}
