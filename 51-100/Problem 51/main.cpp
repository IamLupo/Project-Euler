#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

using namespace std;

/*
	Find the smallest prime which, by replacing part of the number
	(not necessarily adjacent digits) with the same digit,
	is part of an eight prime value family.
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

int toInteger(const vector<int> &v) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i] * pow(10, i);
	
	return r;
}

vector<int> findRepetition(vector<int> &v) {
	int i, j;
	vector<int> t, r;
	
	//Init
	for(i = 0; i < 10; i++)
		t.push_back(0);
	
	//Count values
	for(i = 0; i < v.size(); i++)
		t[v[i]]++;
	
	//Loop results
	for(i = 0; i < t.size(); i++) {
		// if number has multiple collisions
		if(t[i] > 1) {
			//Store the number
			r.push_back(i);
		}
	}
	
	return r;
}

int findSmallestFamily(int target, int l) {
	int i, j, k, x, z, c;
	vector<int> t, t2, v;
	
	for(i = 0; i < primes.size(); i++) {
		t = toVector(primes[i]);
		v = findRepetition(t);

		if( primes[i] >= pow(10, l - 1) &&
			primes[i] <= pow(10, l) &&
			v.size() > 0) {
			
			for(j = 0; j < v.size(); j++) {
				c = 0;
				
				for(x = 0; x < 10; x++) {
					t2 = t;
					
					//replace part
					for(k = 0; k < t2.size(); k++)
						if(t2[k] == v[j])
							t2[k] = x;
					
					z = toInteger(t2);
					if(isPrime(z) && z >= pow(10, l - 1))
						c++;
				}
				
				if(c >= target)
					return primes[i];
			}
		}
	}
	
	return -1;
}

int main() {
	genPrime(1000);

	cout << "result = " << findSmallestFamily(8, 6) << endl;
	
	return 0;
}