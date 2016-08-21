#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	Find ∑c for c < 120000.
*/

static IamLupo::Primes primes;

/*
	The product of the distinct prime numbers dividing n
	
	Example:
		504 = 2^3 * 3^2 * 7
		
		rad(504) = 2 * 3 * 7 = 42
	
	Reference:
		https://en.wikipedia.org/wiki/Radical_of_an_integer
*/
vector<long long> rad_list(int l) {
	int i, j;
	vector<long long> r(l + 1, 1);
	
	for(i = 0; i < primes.size() && primes[i] <= l; i++)
		for(j = primes[i]; j <= l; j += primes[i])
			r[j] *= primes[i];
	
	return r;
}

long long f(int l) {
	int a, b, c;
	long long r;
	vector<long long> rad;
	
	//Init
	r = 0;
	rad = rad_list(l);
	
	for(c = 1; c < l; c++) {
		for(a = 1; a <= (c / 2) && rad[c] < c; a++) {
			b = c - a;
			
			if(rad[a] * rad[b] * rad[c] < c && IamLupo::Math::gcd(a, b) == 1)
				r += c;
		}
	}
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(120000);
	
	cout << "Result = " << f(120000) << endl;
	
	return 0;
}
