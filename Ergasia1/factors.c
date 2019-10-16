#include "functions.h"
#include <stdlib.h>

int* factors(int m, int M, int d){
	int j;
	m_power=malloc(coords*sizeof(int));
	for(j=0; j<coords; j++){
		m_power[j] = modulo_calc(m, (coords-1) - j, M);			// Ypologizw kai apothikeuw ola ta m^(coords-1)-j % M giati einai 128 ki 													epanaxrisopoiountai polles fores
	}
}
