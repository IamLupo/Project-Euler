#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	What is the smallest odd composite that cannot be written as the sum of a
	prime and twice a square?
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

int smallestOddComposite() {
	int i, j, t;
	bool f;
	
	for(i = 3; i < primes.size(); i += 2) {
		if(!isPrime(i)) {
			f = false;
			t = 1;
			
			if(isPrime(i - 2))
				f = true;
			
			for(j = 0; t > 0 && !f; j++) {
				t = i - ((j * j) * 2);
				
				if(isPrime(t))
					f = true;
			}
			
			if(!f)
				return i;
		}
	}
	
	return -1;
}

int main() {
	genPrime(250);
	
	cout << "result = " << smallestOddComposite() << endl;
	
	return 0;
}