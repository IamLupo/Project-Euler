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
	What 12-digit number do you form by concatenating the three terms in this sequence?
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

vector<int> toVector(int v) {
	vector<int> r;
	
	while(v != 0) {
		r.push_back(v % 10);
		v /= 10;
	}
	
	return r;
}

int toInteger(vector<int> v) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i] * pow(10, i);
	
	return r;
}

vector<int> checkList(vector<int> v) {
	int i, j, t;
	vector<int> r;
	vector<int>::iterator it;
	
	for(i = 1; i < v.size(); i++) {
		for(j = 0; j < i; j++) {
			t = (v[i] > v[j]) ? v[i] + v[i] - v[j] : v[j] + v[j] - v[i];
			
			it = find(v.begin(), v.end(), t);
			if(it != v.end() && t > 999) {
				r.push_back(v[j]);
				r.push_back(v[i]);
				r.push_back(t);
				
				return r;
			}
		}
	}
	
	return r;
}

long long findArithmeticSequence() {
	int i, j, t;
	vector<int> v, v2, l, r;
	
	for(i = 0; i < primes.size(); i++) {
		if(primes[i] > 999) {
			l.clear();
			v = toVector(primes[i]);
			sort(v.begin(), v.end());
			
			do {
				t = toInteger(v);

				if(t > 999 && isPrime(t))
					l.push_back(t);
				
			} while(next_permutation(v.begin(), v.end()));
			
			if(l.size() >= 3) {
				sort(l.begin(), l.end());
				
				r = checkList(l);
				if(r.size() == 3 && r[0] != 1487)
					return r[0] * pow(10, 8) + r[1] * pow(10, 4) + r[2];
			}
		}
	}
	
	return -1;
}

int main() {
	genPrime(100);
	
	cout << "result = " << findArithmeticSequence() << endl;
	
	return 0;
}