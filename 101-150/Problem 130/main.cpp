#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	Find the sum of the first twenty-five composite values of n for which
	GCD(n, 10) = 1 and n − 1 is divisible by A(n).
*/

static IamLupo::Primes primes;

static vector<int> digit = {1, 3, 7, 9};

long long f(int l) {
	int i, v, n, k, c;
	vector<int> r;
	
	//Init
	v = 0;
	
	while(true) {
		for(i = 0; i < digit.size(); i++) {
			//Generate a number
			n = v + digit[i];
			
			if(n > 5 && !IamLupo::Prime::is(primes, n)) {
				//Init
				k = 1;
				c = 1;
				
				//Generate k
				while(c % n != 0) {
					c %= n;
					c *= 10;
					c += 1;
					k++;
				}
				
				//Found rare composite value
				if((n - 1) % k == 0) {
					//Save result
					r.push_back(n);
					
					// Check we reached limit
					if(r.size() == l)
						return accumulate(r.begin(), r.end(), (long long)0);
				}
			}
		}
		v += 10;
	}
	
	return -1; // Unknown error :$
}

int main() {
	primes = IamLupo::Prime::generate(150);
	
	cout << "Result = " << f(25) << endl;
	
	return 0;
}
