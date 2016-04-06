#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/vector.h"

using namespace std;

/*
	Find the sum of all numbers, less than one million,
	which are palindromic in base 10 and base 2.
*/

static IamLupo::Primes primes;

int sumTruncatablePrimes() {
	int i, j, k, t;
	vector<int> v, l;
	bool f;
	
	for(i = 4; i < primes.size(); i++) { // first 4 primes are not allowed {2, 3, 7 and 9}
		f = true;
		
		v = IamLupo::Vector::to(primes[i]);
		reverse(v.begin(), v.end());
		
		for(j = 1; j < v.size() && f; j++) { //check length
			//left to right
			t = 0;

			for(k = 0; k < j; k++)
				t += v[k] * pow(10, k);
			
			if(!IamLupo::Prime::is(primes, t))
				f = false;
			
			//right to left
			t = 0;

			for(k = 0; k < j; k++)
				t += v[v.size() - 1 - k] * pow(10, j - 1 - k);
			
			if(!IamLupo::Prime::is(primes, t))
				f = false;
		}
		
		if(f)
			l.push_back(primes[i]);
	}
	
	return accumulate(l.begin(), l.end(), 0);
}

int main() {
	primes = IamLupo::Prime::generate(1000000);
	
	cout << "result = " << sumTruncatablePrimes() << endl;
	
	return 0;
}