int concut(struct **h_func h, int k){
	int g=0;
	g+=h[z][0].h_sum<<24;								
	g+=h[z][1].h_sum<<16;
	g+=h[z][2].h_sum<<8;
	g+=h[z][3].h_sum;
	final = g % (TableSize);

	for(i=0; i<k; i++){
		g+=h[k].h_sum<<(32 - 8*(i+1));								
	} 
	
	return g;
}
