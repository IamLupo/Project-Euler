#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	How many different ways can one hundred be written as
	a sum of at least two positive integers?
*/

static IamLupo::Primes primes;

int countWays(int n) {
	int i, j;
	vector<long long> a(n + 1, 0);
	
	//Init
	a[0] = 1;
	
	//Calc
	for(i = 0; i < primes.size(); i++) {
		for(j = primes[i]; j <= n; j++) {
			a[j] += a[j - primes[i]];
		}
	}
	
	return a[n];
}

int findFirst(int l) {
	int r;
	
	r = 1;
	
	while(r < 1000000) {
		if(countWays(r) >= l)
			return r;
		
		r++;
	}
	
	return -1;
}

int main() {
	IamLupo::Prime::generate(primes, 100);
	
	cout << "result = " << findFirst(5000) << endl;

	return 0;
}