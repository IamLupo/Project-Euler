#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	What is the index of the first term in the Fibonacci sequence
	to contain 1000 digits?
*/

int findFibonacciIndexWithDigits(int length) {
	int index;
	mpz_t x, y, sum;
	
	//Init
	index = 3;
	mpz_init_set_ui(x, 1);
	mpz_init_set_ui(y, 1);
	mpz_init(sum);
	
	while(1) {
		mpz_add(sum, x, y);
		mpz_set(x, y);
		mpz_set(y, sum);
		index++;
		
		if(length <= mpz_sizeinbase(sum, 10))
			return index;
	}
}

int main() {
	printf("index = %d\n", findFibonacciIndexWithDigits(1000));
	
	return 0;
}