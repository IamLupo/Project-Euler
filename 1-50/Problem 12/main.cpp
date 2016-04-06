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
	What is the value of the first triangle number to have over five hundred divisors?
*/

static IamLupo::Primes primes;

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
			//that residual t is the last prime factor with an e = 1 
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
	primes = IamLupo::Prime::generate(10000);
	
	cout << "result = " << firstDivider2(500) << endl;

	return 0;
}