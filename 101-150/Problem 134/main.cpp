#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	Find ∑ S for every pair of consecutive primes with 5 ≤ p1 ≤ 1000000.
*/

/*
	Data:
		f(19, 23) = 53 * 23 = 1219
*/

static IamLupo::Primes primes;

long long find(int p1, int p2) {
	int m;
	long long r;
	
	//generate modulo
	m = 1;
	while(m < p1)
		m *= 10;
	
	//Find answer
	r = p2 + p2;
	while(p1 != r % m)
		r += p2;
	
	cout << p1 << " " << p2 << " " << (r / p2) << " " << r << endl;
	
	return r;
}

string f(int l) {
	int i;
	mpz_t r;
	
	//Init
	mpz_init_set_ui(r, 0);
	
	for(i = 2; i < primes.size() && primes[i] <= l; i++)
		mpz_add_ui(r, r, find(primes[i], primes[i + 1]));
	
	return mpz_get_str(nullptr, 10, r);
}

int main() {
	primes = IamLupo::Prime::generate(1001000);

	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
