#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

using namespace std;

/*
	Which prime, below one-million, can be written as the sum
	of the most consecutive primes?
*/

static vector<int> primes;

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

int findMostConsecutivePrimes(int m) {
	int i, v, l, r, p;
	
	r = 0;		// highest result we generate
	l = 0;		// length of added primes to generate a valid prime
	v = 0;		// generated value
	p = 0;		// position of prime we need to subtract
	
	// Find the first one in a row added prime
	for(i = 0; i < primes.size() && v + primes[i] < m; i++)
		v += primes[i];
	
	// try looking for a new prime number that has a higher length of primes
	while(l < i - p) {
		v -= primes[p];
		p++;
		
		// the generated prime number must not be higher then our max
		if(v + primes[i] < m) {
			v += primes[i];
			i++;
		}
		
		if(isPrime(v)) {
			l = i - p;
			r = v;
		}
	}
	
	return r;
}

int main() {
	genPrime(1000);

	cout << "result = " << findMostConsecutivePrimes(1000000) << endl;
	
	return 0;
}