#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	Find the sum of all numbers, less than one million,
	which are palindromic in base 10 and base 2.
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

int sumTruncatablePrimes() {
	int i, j, k, t;
	vector<int> v, l, l2;
	vector<int>::iterator it;
	bool f;
	
	for(i = 0; i < primes.size(); i++) { //Prime nr
		f = true;
		l2 = l;
		v.clear();
		
		for(j = primes[i]; j != 0; j /= 10)
			v.push_back(j % 10);
		
		if(v.size() < 2)
			f = false;
		
		for(j = 1; j < v.size() && f; j++) { //check length
			//left to right
			t = 0;

			for(k = 0; k < j; k++)
				t += v[k] * pow(10, k);
			
			if(!isPrime(t))
				f = false;
			
			//right to left
			t = 0;

			for(k = 0; k < j; k++)
				t += v[v.size() - 1 - k] * pow(10, j - 1 - k);
			
			if(!isPrime(t))
				f = false;
		}
		
		if(f)
			l.push_back(primes[i]);
	}
	
	return accumulate(l.begin(), l.end(), 0);
}

int main() {
	genPrime(880);
	
	cout << "result = " << sumTruncatablePrimes() << endl;
	
	return 0;
}