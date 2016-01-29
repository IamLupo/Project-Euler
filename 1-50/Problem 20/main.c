#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	Find the sum of the digits in the number 100!
*/
uint64_t getFactorialDigitSum(int x) {
	int i, length;
	mpz_t z, value, sum;
	
	mpz_init(value);
	mpz_init_set_ui(sum, 0);
	mpz_init_set_ui(z, 1);
	
	for(i = 2; i <= x; i++) {
		mpz_mul_ui(z, z, i);
	}
	
	length = mpz_sizeinbase(z, 10);
	for(i = 0; i < length; i++) {
		mpz_mod_ui(value, z, 10);
		mpz_add(sum, sum, value);
		mpz_div_ui(z, z, 10);
	}
	
	mpz_out_str(stdout, 10, sum);
}

int main() {
	printf("sum = ");
	getFactorialDigitSum(100);
	printf("\n");
	
	return 0;
}