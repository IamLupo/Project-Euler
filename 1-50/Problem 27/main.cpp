#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
	Find the product of the coefficients, a and b, for the quadratic expression
	that produces the maximum number of primes for consecutive values of n.
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

int findQuadraticProduct() {
	int a, b, n;
	bool f;
	vector<int> r = {0, 0, 0};
	
	for(a = -1000; a < 1000; a++) {
		for(b = -1000; b < 1000; b++) {
			f = true;
			n = 0;
			
			while(f) {
				//Check if the calculation generate a prime
				if(!isPrime((n * n) + (a * n) + b))
					f = false;
				
				//Save result
				if(n > r[0]) {
					r.clear();
					r.push_back(n);
					r.push_back(a);
					r.push_back(b);
				}
				
				n++;
			}
		}
	}
	
	return r[1] * r[2];
}

int main() {
	//Generate Array of primes between a range of 1 and 1681
	genPrime(41);
	
	//Draw Result
	cout << "result = " << findQuadraticProduct() << endl;
	
	return 0;
}