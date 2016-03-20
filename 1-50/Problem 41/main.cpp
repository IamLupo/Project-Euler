#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/number.h"

using namespace std;

/*
	What is the largest n-digit pandigital prime that exists?
*/

static IamLupo::Primes primes;

int getLargestPandigitalPrime(int s) {
	int i, t, r;
	vector<int> v;
	
	//Init
	r = 0;
	
	//Generate number
	for(i = 1; i <= s; i++)
		v.push_back(i);
	
	do {
		//get generated number
		t = IamLupo::Number::to(v);
		
		//Is the number prime?
		if(IamLupo::Prime::is(primes, t)) {
			//Save the highest number
			if(t > r)
				r = t;
		}
			
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(3163); // 3163 * 3163 =+- 10.000.000
	
	cout << "result = " << getLargestPandigitalPrime(7) << endl;
	
	return 0;
}