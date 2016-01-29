#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	What is the largest n-digit pandigital prime that exists?
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

int toInteger(const vector<int> &v) {
	int i, t;
	
	t = 0;
	
	for(i = 0; i < v.size(); i++)
		t += v[i] * pow(10, i);
	
	return t;
}

int getLargestPandigitalPrime(int s) {
	int i, t, r;
	vector<int> v;
	
	//Init
	r = 0;
	
	//Generate number
	for(i = 1; i <= s; i++)
		v.push_back(i);
	
	do {
		//get generated number
		t = toInteger(v);
		
		//Is the number prime?
		if(isPrime(t)) {
			//Save the highest number
			if(t > r)
				r = t;
		}
			
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	//Generate primes till 9 milion
	genPrime(3000);
	
	cout << "result = " << getLargestPandigitalPrime(7) << endl;
	
	return 0;
}