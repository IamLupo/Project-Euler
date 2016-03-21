#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"
#include "IamLupo/number.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	What 12-digit number do you form by concatenating the three terms in this sequence?
*/

static IamLupo::Primes primes;

/*
	Check for pattern
	
	Example:
		f({1487, 4817, 8147}) = 3330 distance
*/
vector<int> check(vector<int> v) {
	int i, j, t;
	
	for(i = 1; i < v.size() && v.size() >= 3; i++) {
		for(j = 0; j < i && v[i] > 999; j++) {
			t = v[i] + v[i] - v[j];

			if(t > 999 && v[j] > 999 && find(v.begin(), v.end(), t) != v.end())
				return {v[j], v[i], t};
		}
	}
	
	return {};
}

/*
	Generate related prime values
	
	Example:
		f(1487): {1487, 4817, 8147}
*/
vector<int> generate(int n) {
	int v;
	vector<int> d, r;
	
	// Split the digits
	d = IamLupo::Vector::to(n);
	sort(d.begin(), d.end());
	
	//Generate all possible values
	do {
		// Convert digits to a number
		v = IamLupo::Number::to(d);

		//Check if generated value is a prime
		if(IamLupo::Prime::is(primes, v))
			r.push_back(v);
		
	} while(next_permutation(d.begin(), d.end()));
	
	//Sort the values for later purpose
	sort(r.begin(), r.end());
	
	return r;
}

long long findArithmeticSequence() {
	int i;
	vector<int> l, r;
	
	for(i = 168; i < primes.size(); i++) { // 168e primes is first prime with 4 digits
		l = generate(primes[i]);

		r = check(l);
		
		if(r.size() == 3 && r[0] != 1487)
			return r[0] * pow(10, 8) + r[1] * pow(10, 4) + r[2];
	}
	
	return -1; // No answer found
}

int main() {
	primes = IamLupo::Prime::generate(10000);
	
	cout << "result = " << findArithmeticSequence() << endl;
	
	return 0;
}