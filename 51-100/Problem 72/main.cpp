#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/math.h"

using namespace std;

/*
	How many elements would be contained in the set of
	reduced proper fractions for d ≤ 1,000,000?
*/

static IamLupo::Primes primes;

long long countProperFractions(int l) {
	int i, j;
	long long r;
	
	r = 0;
	j = 0;
	
	for(i = 2; i <= l; i++) {
		if(primes[j] == i) {
			r += primes[j] - 1;
			j++;
		}
		else
			r += IamLupo::Math::phi(i);
	}
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(1000000);
	
	cout << "result = " << countProperFractions(1000000) << endl;
	
	return 0;
}