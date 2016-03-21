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
	What is the smallest odd composite that cannot be written as the sum of a
	prime and twice a square?
*/

static IamLupo::Primes primes;

int smallestOddComposite() {
	int i, j, t;
	bool f;
	
	for(i = 5; i < 10000; i += 2) {
		if(!IamLupo::Prime::is(primes, i)) {
			f = false;
			t = 1;
			
			if(IamLupo::Prime::is(primes, i - 2))
				f = true;
			
			for(j = 0; i > t && !f; j++) {
				t = pow(j, 2) * 2;
				
				if(i > t && IamLupo::Prime::is(primes, i - t))
					f = true;
			}
			
			if(!f)
				return i;
		}
	}
	
	return -1; // No result found
}

int main() {
	primes = IamLupo::Prime::generate(6000);
	
	cout << "result = " << smallestOddComposite() << endl;
	
	return 0;
}