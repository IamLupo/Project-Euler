#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	Find the product of the coefficients, a and b, for the quadratic expression
	that produces the maximum number of primes for consecutive values of n.
*/

static IamLupo::Primes primes;

int findQuadraticProduct(int a_max, int b_max) {
	int a, b, n;
	bool f, neg;
	vector<int> r = {0, 0, 0};
	
	for(a = 0; a < primes.size() && primes[a] < a_max; a++) {
		for(b = 0; b < primes.size() && primes[b] < b_max; b++) {
			f = true;
			n = 0;
			
			while(f) {
				//Check if the calculation generate a prime
				if(!IamLupo::Prime::is(primes, (n * n) + (primes[a] * n * - 1) + primes[b]))
					f = false;
				
				//Save result
				if(n > r[0] && r[2] < primes[b]) {
					r.clear();
					r.push_back(n);
					r.push_back(primes[a] * - 1);
					r.push_back(primes[b]);
				}
				
				n++;
			}
		}
	}
	
	return r[1] * r[2];
}

int main() {
	primes = IamLupo::Prime::generate(10000);
	
	cout << "result = " << findQuadraticProduct(100, 1000) << endl;
	
	return 0;
}