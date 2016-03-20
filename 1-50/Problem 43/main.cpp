#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/number.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	Find the sum of all 0 to 9 pandigital numbers with this property.
*/

static IamLupo::Primes primes;

long long sumPandigital() {
	int i;
	long long r;
	vector<int> v;
	bool f;
	
	r = 0;
	v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	do {
		f = true;
		
		for(i = 0; i < 7 && f; i++) {
			vector<int> v2(v.end() - i - 4, v.end() - i - 1);
			
			if(IamLupo::Number::to(v2) % primes[i] != 0)
				f = false;
		}
		
		if(f)
			r += IamLupo::Number::to(v);
		
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(17);
	
	cout << "result = " << sumPandigital() << endl;
	
	return 0;
}