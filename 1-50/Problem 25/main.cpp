#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

/*
	What is the index of the first term in the Fibonacci sequence
	to contain 1000 digits?
*/

using namespace std;

int findFibonacciIndexWithDigits(int l) {
	int i;
	mpz_t x, y, t;
	
	//Init
	i = 3;
	mpz_init_set_ui(x, 1);
	mpz_init_set_ui(y, 1);
	mpz_init(t);
	
	while(1) {
		mpz_add(t, x, y);
		mpz_set(x, y);
		mpz_set(y, t);
		i++;
		
		if(l <= mpz_sizeinbase(t, 10))
			return i;
	}
}

int main() {
	cout << "result = " << findFibonacciIndexWithDigits(1000) << '\n';
	
	return 0;
}
