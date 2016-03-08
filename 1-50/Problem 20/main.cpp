#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

using namespace std;

/*
	Find the sum of the digits in the number 100!
*/

string sumFactorialDigits(int x) {
	int i, l;
	mpz_t z, v, r;
	
	//Init
	mpz_init(v);
	mpz_init_set_ui(r, 0);
	mpz_init_set_ui(z, 1);
	
	//Factorial
	for(i = 2; i <= x; i++)
		mpz_mul_ui(z, z, i);
	
	//Sum digits
	l = mpz_sizeinbase(z, 10);
	for(i = 0; i < l; i++) {
		//Grab digit
		mpz_mod_ui(v, z, 10);
		
		//sum digit
		mpz_add(r, r, v);
		
		//Get next digit
		mpz_div_ui(z, z, 10);
	}
	
	return mpz_get_str(nullptr, 10, r);
}

int main() {
	cout << "result = " << sumFactorialDigits(100) << endl;
	
	return 0;
}