void dtw(struct curve a, struct curve b){
	int i, j;
	struct dwt_cell **dtw_table, min;
	
	dtw_table = malloc(a.noPoints+1 * sizeof(dwt_cell));
	for(i=0; i<a.noPoints+1; i++){
		dtw_table[i] = malloc(b.noPoints+1 * sizeof(dwt_cell));
		for(j=0; j<b.noPoints+1; j++){
			dtw_table[i][j].previous = NULL; 
	}

	for(i=0; i<a.noPoints+1; i++){
		dtw_table[i][[0].value = INFINITY;
	}
	
	for(j=0; j<b.noPoints+1; j++){
		dtw_table[0][[j].value = INFINITY;
	}
	
	for(i=1; i<a.noPoints+1; i++){
		for(j=1; j<b.noPoints+1; j++){
			min = min_neighbour(dtw_table[i-1][j], dtw_table[i-1][j-1], dtw_table[i][j-1]);
			dtw_table[i][j].value = min.value + (a.points[i].x - b.points[i].x) + (a.points[i].y - b.points[i].y);
			dtw_table[i][j].previous = min;
		}
	}
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

backtrack(struct dtw_cell **dtw_table){

 

			
