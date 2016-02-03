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
	Find the lowest sum for a set of five primes for which any
	two primes concatenate to produce another prime.
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

int sum(vector<int> v) {
	int i, s;
	
	s = 0;
	for(i = 0; i < v.size(); i++)
		s += v[i];
	
	return s;
}

/*
	It will give the next base number of a value

	Example:
		f(5) = 10
		f(9) = 10
		f(11) = 100
		f(55) = 100
		f(101) = 1000
*/
int nextBase10(int v) {
	int n;

	n = 1;
	
	while((v / n) != 0)
		n *= 10;
	
	return n;
}

/*
	Example:
		f({3}, 5) = false, because 35 isnt prime
		f({3, 7}, 13) = false, because 133 and 713 isnt a prime
		f({3, 7}, 109) = true, because 3109, 1093, 1097 and 7109 are prime
*/
bool isConcatenatePrime(const vector<int> &r, int v) {
	int i;
	
	for(i = 0; i < r.size(); i++) {
		if(!isPrime2((v * nextBase10(r[i])) + r[i]))
			return false;
		
		if(!isPrime2((r[i] * nextBase10(v)) + v))
			return false;
	}
	
	return true;
}

void brutforce(vector<int> &r, int* m, int index, int max) {
	int s;
	vector<int> t;
	
	if(r.size() == max) {
		//Calculate the new max value
		*m = sum(r);
		return;
	}
	
	//Calculate the sum of the valide values
	s = sum(r);
	
	/*
		rules:
			the prime index can never be out of range
			if there is no known max value we will run this
			if s + next prime is still lower then the max value
	*/
	while(  (*m == -1 && primes[index] != 0) ||
			(*m < s + primes[index] && primes[index] != 0)) {
		
		/*
			check if index prime van be fit with the already found primes list
		*/
		if(isConcatenatePrime(r, primes[index])) {
			//Copy already valid primes
			t = r;
			
			//Push the new prime in the list
			t.push_back(primes[index]);
			
			//Start a new generation
			brutforce(t, m, index + 1, max);
		}
		
		index++;
	}
}

int sumConcatenatePrimes(int l) {
	int m;
	vector<int> r;
	
	m = -1; //Unknown minimal sum
	
	brutforce(r, &m, 0, l);
	
	return m;
}

int main() {
	genPrime(100);
	
	cout << "result = " << sumConcatenatePrimes(5) << endl;
	
	return 0;
}