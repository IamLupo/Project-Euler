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
	Find the sum of all the primes below one-hundred thousand
	that will never be a factor of R(10^n).
*/

static IamLupo::Primes primes;

int A(int n) {
	int k, c;
	
	//Init
	k = 1;
	c = 1;
	
	//Generate k
	while(c % n != 0) {
		c %= n;
		c *= 10;
		c += 1;
		k++;
	}
	
	return k;
}

long long f(int l) {
	int i;
	long long r;
	
	//Init
	r = 0; 
	
	for(i = 0; i < primes.size() && primes[i] <= l; i++)
		if(primes[i] != 2 && primes[i] != 5) {
			if(10000000000000000 % A(primes[i]) != 0)
				r += primes[i];
		}
		else
			r += primes[i];
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(100000);

	cout << "Result = " << f(100000) << endl;

	return 0;
}
