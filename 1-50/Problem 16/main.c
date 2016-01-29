#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	What is the sum of the digits of the number 2^1000?
*/
uint64_t getSum(int x, int y) {
	int i, length;
	mpz_t z, value, sum;
	
	mpz_init(value);
	mpz_init_set_ui(sum, 0);
	mpz_init_set_ui(z, x);
	
	//z = x^y
	mpz_pow_ui(z, z, y);
	length = mpz_sizeinbase(z, 10);
	
	//Loop the values and add them
	for(i = 0; i < length; i++) {
		mpz_mod_ui(value, z, 10);
		mpz_add(sum, sum, value);
		mpz_div_ui(z, z, 10);
	}
	
	mpz_out_str(stdout, 10, sum);
}

int main() {
	printf("sum = ");
	getSum(2, 1000);
	printf("\n");
	
	return 0;
}