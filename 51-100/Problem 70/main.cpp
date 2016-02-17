#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#include "IamLupo/prime.h"
#include "IamLupo/math.h"
#include "IamLupo/permutation.h"

/*
	Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation
	of n and the ratio n/φ(n) produces a minimum.
*/

static IamLupo::Primes primes;

int getMinimumPhiPermutation(int l) {
	int i, j, r, v, p, tt;
	double t, h;
	
	h = 100.0;
	
	for(i = 0; i < primes.size(); i++) {
		tt = primes[i];
		for(j = 0; j < primes.size(); j++) {
			v = tt * primes[j];
			if(v < l) {
				p = IamLupo::Math::phi(v);
				t = (double)v / p;
				
				if(h > t && IamLupo::Permutation::is(v, p)) {
					h = t;
					r = v;
				}
			}
		}
	}
	
	return r;
}

int main() {
	IamLupo::Prime::generate(primes, 60);
	
	cout << "result = " << getMinimumPhiPermutation(10000000) << endl;
	
	return 0;
}