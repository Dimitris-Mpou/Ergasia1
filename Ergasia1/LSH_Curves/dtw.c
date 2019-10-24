#include <stdlib.h>
#include <math.h>

int dtw(struct curve a, struct curve b){
	int i, j;
	struct dwt_cell **dtw_table, min;
	
	dtw_table = malloc(a.noPoints * sizeof(dwt_cell));
	for(i=0; i<a.noPoints; i++){
		dtw_table[i] = malloc(b.noPoints * sizeof(dwt_cell));
		for(j=0; j<b.noPoints; j++){
			dtw_table[i][j].previous = NULL; 
	}

	for(i=0; i<a.noPoints; i++){								//Arxikopoioume thn prwth sthlh
		dtw_table[i][[0].value = euclidean(a.points[i], b.points[0]);
	}
	
	for(j=0; j<b.noPoints; j++){
		dtw_table[0][[j].value = euclidean(a.points[0], b.points[j]);;			//Arxikopoioume thn prwth grammh
	}
	
	for(i=1; i<a.noPoints; i++){
		for(j=1; j<b.noPoints; j++){
			min = min_neighbour(dtw_table[i-1][j], dtw_table[i-1][j-1], dtw_table[i][j-1]);
			dtw_table[i][j].value = min.value + euclidean(a.points[i], b.points[i]);
			dtw_table[i][j].previous = min;
		}
	}

	return dtw[a.noPoints-1][b.noPoints-1];
}
	
struct dtw_cell min_neighbour(struct dtw_cell a, struct dtw_cell b, struct dtw_cell c){
	if(a.value < b.value){
		if(a.value <= c.value){
			return a;
		}
		else{
			return c;
		}
	else{
		if(b.value <= c.value){
			return b;
		}
		else{
			return c;
		}
	}
}

double euclidean(struct point a, struct point b){
	return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 1/2);
}


 

			
