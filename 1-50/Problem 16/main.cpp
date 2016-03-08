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
	What is the sum of the digits of the number 2^1000?
*/

string sum(int x, int y) {
	int i, l;
	mpz_t z, v, r;
	
	//Init
	mpz_init(v);
	mpz_init_set_ui(r, 0);
	mpz_init_set_ui(z, x);
	
	//z = x^y
	mpz_pow_ui(z, z, y);
	
	//Loop the values and add them
	l = mpz_sizeinbase(z, 10);
	for(i = 0; i < l; i++) {
		//Grab digit
		mpz_mod_ui(v, z, 10);
		
		//Add digit
		mpz_add(r, r, v);
		
		//Go to next digit
		mpz_div_ui(z, z, 10);
	}
	
	return mpz_get_str(nullptr, 10, r);
}

int main() {
	cout << "result = " << sum(2, 1000) << endl;
	
	return 0;
}
