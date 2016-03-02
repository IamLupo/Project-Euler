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
	Find the last ten digits of this prime number.
*/

string findLastDigits(int m, int p) {
	int r;
	string s;
	mpz_t a;
	
	//Init
	mpz_init_set_ui(a, 2);
	
	// m * 2^p + 1
	mpz_pow_ui(a, a, p);
	mpz_mul_ui(a, a, m);
	mpz_add_ui(a, a, 1);
	
	s = mpz_get_str(nullptr, 10, a);
	
	return s.substr(s.size() - 10, 10);
}

int main() {
	cout << "result = " << findLastDigits(28433, 7830457) << endl;
	
	return 0;
}
