#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	How many circular primes are there below one million?
*/

static vector<int> primes;

/* BROKE: need a fix */
bool isPrime2(int v) {
	int i, e, p, c;
	
	if(v <= 1)
		return false;
	
	c = 0;
	e = primes.size() / 2;
	p = e;
	
	while(c < 3) {
		if(primes[p] == v)
			return true;
		else if(primes[p] > v)
			p -= e;
		else if(primes[p] < v)
			p += e;
		
		if(e % 2 == 0)
			e = e / 2;
		else
			e = (e / 2) + 1;
		
		if(e == 1)
			c++;
	}
	
	return false;
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

int countCircularPrimes() {
	int i, j, k, t;
	vector<int> v, l, l2;
	vector<int>::iterator it;
	bool f;
	
	for(i = 0; i < primes.size(); i++) {
		t = primes[i];
		f = true;
		
		l2.clear();
		v.clear();
		l2 = l;
		
		/*
			Extract number in parts
			Example: f(135) = [1, 3, 5]
		*/
		while(t != 0) {
			v.push_back(t % 10);
			t /= 10;
		}
		
		/*
			Circular primes has v size possebilities
			Example: 197, 971, and 719
		*/
		for(j = 0; j < v.size(); j++) {
			t = 0;
			
			//Generate Circular prime
			for(k = 0; k < v.size(); k++)
				t += v[(j + k) % v.size()] * pow(10, k);
			
			//Check if prime
			if(!isPrime(t))
				f = false;
			
			//Add prime if not exist in list
			it = find(l2.begin(), l2.end(), t);
			if(it == l2.end())
				l2.push_back(t);
			
		}
		
		//If no mistakes where made update the main list with new results
		if(f)
			l = l2;
	}
	
	//Count results
	return l.size();
}

int main() {
	//Generate Array of primes between a range of 1 and 1000000
	genPrime(1000);
	
	cout << "result = " << countCircularPrimes() << endl;
	
	return 0;
}