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

static IamLupo::Primes primes;

unsigned long long f(int l) {
	int i;
	unsigned long long k, r, x, y;
	mpz_t v, mod;
	
	//Init
	mpz_init(v);
	mpz_init(mod);
	k = 10;
	r = 0;
	
	for(i = 2; i < primes.size() && primes[i] <= l; i++) {
		if(primes[i] > k)
			k *= 10;
		
		// Set
		mpz_set_ui(v, primes[i + 1]);
		mpz_set_ui(mod, k);
		
		// Get multiplier for next prime
		mpz_powm_ui(v, v, (k / 10 * 4) - 1, mod);
		mpz_mul_ui(v, v, primes[i]);
		mpz_mod(v, v, mod);
		
		// r += v * p2
		r += primes[i + 1] * mpz_get_ui(v);
	}
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(1001000);
	
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
