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
	Find the least value of n for which the remainder first exceeds 10^10.
*/

static IamLupo::Primes primes;

long long f(int p) {
	int i, c;
	
	//c = (prime index + 1) * 2
	c = 2;
	
	// Loop even prime index id's
	for(i = 0; i < primes.size(); i += 2) { 
		//Debug
		//cout << primes[i] * c << ", ";
		
		// Check results
		if(primes[i] * c > pow(10, p))
			return i + 1;
		
		//Generate next generation
		c += 4;
	}
	
	return -1; // Unknown
}

int main() {
	primes = IamLupo::Prime::generate(240000);
	
	cout << "Result = " << f(10) << endl;
	
	return 0;
}
