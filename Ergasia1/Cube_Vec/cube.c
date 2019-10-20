#include <stdlib.h>
#include <time.h>
#include "headers.h"
#include <math.h>

void cube_train(unsigned int **g, struct list_node ***f, struct list_node **cube, int vec_sum, int d){
	int i, j, hash_pos, cube_pos;
	char binary_string[d];
	struct list_node *cur;

	srand(time(0));
	for(i=0; i<vec_sum; i++){
		for(j=0; j<d; j++){
			hash_pos = g[i][j] % 4999;
			if(f[j][hash_pos ] == NULL){
				f[j][hash_pos] = malloc(sizeof(struct list_node));
				f[j][hash_pos]->next = NULL;
				f[j][hash_pos]->g = g[i][j];
				f[j][hash_pos]->vec_pos = rand() % 2;
				binary_string[j] = f[j][hash_pos]->vec_pos;
			}else{
				cur = f[j][hash_pos];
				while(cur->next!=NULL && cur->g!=g[i][j]){
					cur = cur->next;
				}
				if(cur->g != g[i][j]){
					cur->next = malloc(sizeof(struct list_node));
					cur->next->g = g[i][j];
					cur->next->next = NULL;
					cur->next->vec_pos = rand() % 2;
				}
				binary_string[j] = f[j][hash_pos]->vec_pos; 
			}	
			binary_string[d+1] = '\0';
		}
		cube_pos = 0;		// int
		for(j=0; j<d; j++){
			cube_pos += atoi(binary_string[j]) * pow(2,d-1 -j);	// math.h
		}
		if(cube[cube_pos] == NULL){								// struct list_node **cube
			cube[cube_pos] = malloc(sizeof(struct list_node));
			cube[cube_pos]->next = NULL;
			cube[cube_pos]->vec_pos = i;
		}else{
			cur = cube[cube_pos];
			while(cur->next!=NULL){
				cur = cur->next;
			}
			cur->next = malloc(sizeof(struct list_node));
			cur->next->next = NULL;
			cur->next->vec_pos = i;
		}
	}
}
// Στα 2 πααραπανω σημεια η οποια θα φτιαχνει μια σειρα απο 0 και 1
// Και στο 3ο πρεπει να εισαγει το διανυσμα σε μια κορυφη του κυβου αναλογα με το αποτελεσμα της συμβολοσειρας, οπως και στο αλλο ερωτημα ετσι κι εδω δεν θα αποθηκευουμε ολο το διανυσμα αλλα μονο το i, δηλαδη το position του στο vectors[i]
