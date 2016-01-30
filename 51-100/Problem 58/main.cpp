#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"

using namespace std;

/*
	what is the side length of the square spiral for which the ratio of
	primes along both diagonals first falls below 10%?
*/

static vector<int> primes;

bool isPrime2(long long v) {
	int i;
	
	for(i = 0; i < primes.size() && primes[i] < v / 2; i++) {
		if(v % primes[i] == 0)
			return false;
	}
	
	return true;
}

bool isPrime(int v) {
	vector<int>::iterator it;
	
	it = find(primes.begin(), primes.end(), v);
	if(it != primes.end())
		return true;
	
	return false;
}

void genPrime(int m) {
	int i, j;
	vector<int> a, b;
	
	for(i = 2; i <= m * m; i++)
		a.push_back(i);
	
	for(i = 2; i <= m; i++) {
		for(j = 0; j < a.size(); j++) {
			if(a[j] % i != 0 || a[j] <= i)
				b.push_back(a[j]);
		}
		a = b;
		b.clear();
	}
	
	primes = a;
}

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
		if(isPrime2(v))
			c++;
		i++;
		
		v += d;
		if(isPrime2(v))
			c++;
		i++;
		
		v += d;
		if(isPrime2(v))
			c++;
		i++;

		v += d;
		if(isPrime2(v))
			c++;
		i++;
	} while(i < c * 10);
	
	return d + 1;
}

int main() {
	genPrime(162);
	
	cout << "result = " << countBiggerNumeratorDigit() << endl;
	
	return 0;
}