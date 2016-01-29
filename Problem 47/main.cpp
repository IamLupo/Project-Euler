#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	Find the first four consecutive integers to have four distinct prime factors.
	What is the first of these numbers?
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

bool checkMultiplier(int v, int s, int l, int m) {
	int i, j, t;
	
	if(l == m && v == 1)
		return true;
	
	for(i = s; i < primes.size() && primes[i] <= v && primes[i] <= 700; i++) {
		for(j = 1; pow(primes[i], j) <= v; j++) {
			t = pow(primes[i], j);
			
			if(v % t == 0) {
				t = v / t;
				
				if(checkMultiplier(t, i + 1, l + 1, m))
					return true;
			}
		}
	}
	
	return false;
}

int findConsecutiveIntegers(int l) {
	int i, j, v, r, p;

	for(i = 0; i < primes.size(); i++) {
		if(primes[i + 1] - primes[i] - 1 >= l) {
			v = 0;
			p = primes[i] + 1;
			for(j = p; j < primes[i + 1]; j++) {
				if(checkMultiplier(j, 0, 0, l))
					v++;
				else {
					v = 0;
					p = j;
				}
				
				if(v == l)
					return p + 1;
			}
		}
	}
}

int main() {
	genPrime(1000);

	cout << "result = " << findConsecutiveIntegers(4) << endl;
	
	return 0;
}