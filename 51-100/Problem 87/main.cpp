#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <set>

#include "IamLupo/prime.h"

using namespace std;

/*
	How many numbers below fifty million can be expressed as the sum of a prime square,
	prime cube, and prime fourth power?
*/

static IamLupo::Primes primes;

int countResults(int l) {
	int i, j, k;
	long long t1, t2, t3;
	set<int> r;
	
	for(i = 0; i < primes.size() && pow(primes[i], 2) < l; i++) {
		t1 = pow(primes[i], 2);
		
		for(j = 0; j < primes.size() && t1 + pow(primes[j], 3) < l; j++) {
			t2 = t1 + pow(primes[j], 3);
			
			for(k = 0; k < primes.size() && t2 + pow(primes[k], 4) < l; k++) {
				t3 = t2 + pow(primes[k], 4);
				
				if(t3 < l)
					r.insert(t3);
			}
		}
	}
	
	return r.size();
}

int main() {
	primes = IamLupo::Prime::generate(85);
	
	cout << "result = " << countResults(50000000) << endl;
	
	return 0;
}
