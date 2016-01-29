#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include "gmp.h"

using namespace std;

/*
	Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/

string findSelfPowers(int r) {
	int i;
	char buffer[10000];
	string s;
	mpz_t t, v;
	
	mpz_init(t);
	mpz_init_set_ui(v, 0);
	
	for(i = 1; i <= r; i++) {
		mpz_set_ui(t, i);
		mpz_pow_ui(t, t, i);
		mpz_add(v, v, t);
	}
	
	mpz_get_str(buffer, 10, v);
	s.insert(s.begin(), buffer + strlen(buffer) - 10, buffer + strlen(buffer));
	
	return s;
}

int main() {
	cout << "result = " << findSelfPowers(1000) << endl;
	
	return 0;
}