#include <stdlib.h>
#include <time.h>
#include "headers.h"

void cube_train(unsigned int **g, struct list_node ***f, int vec_sum, int d){
	int i, j, z, flag;
	struct list_node *cur;

	srand(time(0));
	for(i=0; i<vec_sum; i++){
		for(j=0; j<d; j++){
			if(f[j][g[i][j] % 4999] == 	NULL){
				f[j][g[i][j] % 4999] = malloc(sizeof(struct list_node));
				f[j][g[i][j] % 4999]->next = NULL;
				f[j][g[i][j] % 4999]->g = g[i][j];
				f[j][g[i][j] % 4999]->vec_pos = rand() % 2;
				// f[j][g[i][j]%4999]->vec_pos periexei to 0 ή 1
			}else{
				cur = f[j][g[i][j] % 4999];
				while(cur->next!=NULL && cur->g!=g[i][j]){
					cur = cur->next;
				}
				if(cur->g != g[i][j]){
					cur->next = malloc(sizeof(struct list_node));
					cur->next->g = g[i][j];
					cur->next->next = NULL;
					cur->next->vec_pos = rand() % 2;
				}
				//cur->vec_pos periexei to 0 ή 1 
			}
		}
		// Insert in cube
	}
}
// Στα 2 πααραπανω σημεια η οποια θα φτιαχνει μια σειρα απο 0 και 1
// Και στο 3ο πρεπει να εισαγει το διανυσμα σε μια κορυφη του κυβου αναλογα με το αποτελεσμα της συμβολοσειρας, οπως και στο αλλο ερωτημα ετσι κι εδω δεν θα αποθηκευουμε ολο το διανυσμα αλλα μονο το i, δηλαδη το position του στο vectors[i]
