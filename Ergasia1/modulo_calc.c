int modulo_calc(int base, int exponent, int modulus){
	int i,result;

    result=1;
    for(i=0; i < exponent; i++){
        result= (result * base) % modulus;
	}
	return result;
}
