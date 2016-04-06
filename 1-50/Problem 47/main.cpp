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
	Find the first four consecutive integers to have four distinct prime factors.
	What is the first of these numbers?
*/

static IamLupo::Primes primes;

int PrimeFacors(int n) {
	int i, r, t;
	bool pf;
	
	//Init
	r = 0;
	t = n;
	
	for(i = 0; i < primes.size(); i++) {
		if(primes[i] * primes[i] > n)
			return r + 1;

		pf = false;
		
		while (t % primes[i] == 0) {
			pf = true;
			t /= primes[i];
		}
		
		if(pf)
			r++;

		// remainder is to low to find more prime factors
		if(t == 1)
			return r;
	}

	return r;
}

int findConsecutiveIntegers(int l) {
	int c, r;
	
	//Init
	c = 1;				// Found consecutive integers
	r = 2 * 3 * 5 * 7;	// Calc start point to check
	
	while (c < l) {
		r++;
		if(PrimeFacors(r) >= l)
			c++;
		else
			c = 0;
	}
	
	return r - l + 1;
}

int main() {
	primes = IamLupo::Prime::generate(400);
	
	cout << "result = " << findConsecutiveIntegers(4) << endl;
	
	return 0;
}