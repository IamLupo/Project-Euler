#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#include "IamLupo/prime.h"

/*
	Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.
*/

static IamLupo::Primes primes;

/*
	1 / φ(1) = 1
	2 / φ(2) = 2
	6 / φ(6) = 3
	210 / φ(210) = 4
	30030 / φ(30030) = 5
	
	the n value can be generated by multiply prime values
*/
double getHighestPhiValue(int l) {
	int i;
	double r;
	
	r = 1.0;
	
	for(i = 0; i < primes.size() && r * primes[i] < l; i++)
		r *= primes[i];
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(100);
	
	cout << "result = " << getHighestPhiValue(1000000) << endl;
	
	return 0;
}