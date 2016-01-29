#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	What is the value of the first triangle number to have over five hundred divisors?
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

long long firstDivider2(int r) {
	int i, x, c, e;
	long long v, t;
	
	v = 1;
	x = 1;
	c = 0;

	while(c <= r) {
		c = 1;
		x += 1;
		v += x;
		t = v;
		
		for (i = 0; i <= primes.size(); i++) {
			if(primes[i] * primes[i] > t) {
				c *= 2;
				break;
			}
			
			//When the prime divisor would be greater than the residual t, 
			//that residual t is the last prime factor with an e=1 
			//No necessity to identify it.
			e = 1;
			while(t % primes[i] == 0) {
				e++;
				t /= primes[i];
			}
			
			if(e > 1)
				c *= e;
			
			if(t == 1)
				break;
		}
	}
	
	return v;
}

int firstDivider(int s) {
	int i, j, x;
	vector<int> v;
	
	//Init
	for(i = 0; i <= 77000000; i++)
		v.push_back(1);
	
	//Count dividers
	for(i = 2; i < 33500000; i++) {
		for(j = i; j < 77000000; j += i) {
			v[j]++;
		}
	}
	
	//Search the first s
	x = 1;
	for(i = 1; i < 77000000; i += x) {
		if(v[i] >= s)
			return i;
		x++;
	}
	
	return 0;
}

int main() {
	genPrime(1000);
	
	cout << "result = " << firstDivider2(500) << endl;

	return 0;
}