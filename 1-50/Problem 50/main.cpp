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
	Which prime, below one-million, can be written as the sum
	of the most consecutive primes?
*/

static IamLupo::Primes primes;

int findMostConsecutivePrimes(int m) {
	int i, v, l, r, p;
	
	r = 0;		// highest result we generate
	l = 0;		// length of added primes to generate a valid prime
	v = 0;		// generated value
	p = 0;		// position of prime we need to subtract
	
	// Find the first one in a row added prime
	for(i = 0; i < primes.size() && v + primes[i] < m; i++)
		v += primes[i];
	
	// try looking for a new prime number that has a higher length of primes
	while(l < i - p) {
		v -= primes[p];
		p++;
		
		// the generated prime number must not be higher then our max
		if(v + primes[i] < m) {
			v += primes[i];
			i++;
		}
		
		if(IamLupo::Prime::is(primes, v)) {
			l = i - p;
			r = v;
		}
	}
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(1000000);

	cout << "result = " << findMostConsecutivePrimes(1000000) << endl;
	
	return 0;
}