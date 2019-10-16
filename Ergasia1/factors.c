
#include "headers.h"
#include "functions.h"


void factors(int m, int M, int coords, int *m_factors){
	int j;
	for(j=0; j<coords; j++){
		m_factors[j] = modulo_calc(m, (coords-1) - j, M);			// Ypologizw kai apothikeuw ola ta m^(coords-1)-j % M giati einai 128 ki epanaxrisopoiountai polles fores
	}
}
