#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

bool isPerfectSquare(long long n) {
	if (n < 0)
		return false;

	long long x = sqrt(n);
	
	return x * x == n;
}

long long pn(long a, long b, long c) {
	return a * b * b * b * c * c + a * a * c;
}

long long f(long long l) {
	long long a, b, c, n;
	vector<long long> v;
	
	for(a = 1; pn(a, a + 1, a) < l; ++a) {
		for(b = a + 1; pn(a, b, 1) < l; ++b) {
			if(IamLupo::Math::gcd(b, a) == 1) {
				for(c = 1, n = pn(a, b, c); n < l; n = pn(a, b, ++c)) {
					if(isPerfectSquare(n))
						v.push_back(n);
				}
			}
		}
	}
	
	return accumulate(v.begin(), v.end(), (long long)0);
}

int main() {
	//Example
	//cout << "Result = " << f(100000) << endl; // 124657
	
	//Real
	cout << "Result = " << f(1000000000000) << endl;
	
	
	return 0;
}
