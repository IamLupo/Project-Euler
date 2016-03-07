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
	What is the largest prime factor of the number 600851475143 ?
*/

static IamLupo::Primes primes;

int findLargestPrimeFactor(long long v) {
	int i;
	
	for(i = primes.size() - 1; i >= 0; i--)
		if(v % primes[i] == 0)
			return primes[i];
	
	return -1; // Nothing found
}

int main() {
	primes = IamLupo::Prime::generate(83);
	
	cout << "result = " << findLargestPrimeFactor(600851475143) << endl;
	
	return 0;
}
