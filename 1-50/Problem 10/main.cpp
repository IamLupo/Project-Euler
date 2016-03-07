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
	Find the sum of all the primes below two million.
*/

static IamLupo::Primes primes;

long long sumPrimes(int m) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 1; i < m; i++)
		if(IamLupo::Prime::is(primes, i))
			r += i;
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(40);
	
	cout << "result = " << sumPrimes(2000000) << endl;
	
	return 0;
}
