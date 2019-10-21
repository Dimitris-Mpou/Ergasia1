#include <math.h>

void edges(int *binary_string, int *cube_pos, int probes, int d){
	int i, j, hamming_distance;
	hamming_distance = 1;
	
	for(i=0; i<probes; i++){
		cube_pos[i]=0;
	}
	
	for(j=0; j<d; j++){
		cube_pos[0] += binary_string[j]*pow(2,d-1 -j); 
	}
	for(i=1; i<probes; i++){
		if(i<d){
			if(j==i-1){
				if(binary_string[j]==0){
					cube_pos[i] += pow(2,d-1 -j);
				}
			}else{
				cube_pos[i] += binary_string[j]*pow(2,d-1 -j);
			}
		}

	}

}
