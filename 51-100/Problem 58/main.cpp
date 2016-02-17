#include <iostream>

#include "IamLupo/prime.h"

using namespace std;

/*
	what is the side length of the square spiral for which the ratio of
	primes along both diagonals first falls below 10%?
*/

static IamLupo::Primes primes;

int countBiggerNumeratorDigit() {
	int i, c, d;
	long long v;
	
	v = 1;
	d = 0;
	
	c = 0;
	i = 0;
	
	do {
		d += 2;
		
		v += d;
		if(IamLupo::Prime::is(primes, v))
			c++;
		i++;
		
		v += d;
		if(IamLupo::Prime::is(primes, v))
			c++;
		i++;
		
		v += d;
		if(IamLupo::Prime::is(primes, v))
			c++;
		i++;

		v += d;
		if(IamLupo::Prime::is(primes, v))
			c++;
		i++;
	} while(i < c * 10);
	
	return d + 1;
}

int main() {
	IamLupo::Prime::generate(primes, 260);

	cout << "result = " << countBiggerNumeratorDigit() << endl;
	
	return 0;
}