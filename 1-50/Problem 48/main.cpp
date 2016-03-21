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
	Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/

string findSelfPowers(int l) {
	int i;
	string s;
	mpz_t t, v;
	
	//Init
	mpz_init(t);
	mpz_init_set_ui(v, 0);
	
	for(i = 1; i <= l; i++) {
		//v += i^i
		mpz_set_ui(t, i);
		mpz_pow_ui(t, t, i);
		mpz_add(v, v, t);
	}
	
	//Convert
	s = mpz_get_str(nullptr, 10, v);
	
	//return the last 10 charters
	return s.substr(s.size() - 10, 10);
}

int main() {
	cout << "result = " << findSelfPowers(1000) << endl;
	
	return 0;
}