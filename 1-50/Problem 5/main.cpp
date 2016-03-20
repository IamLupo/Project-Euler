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
	What is the smallest positive number that is evenly divisible by al
	of the numbers from 1 to 20?
*/

static IamLupo::Primes primes;

int findPrimeFactorId(int v) {
	int i;
	
	for(i = 0; i < primes.size(); i++)
		if(v % primes[i] == 0)
			return i;
	
	return -1;
}

int smallestOfRange(int min, int max) {
	int i, v, id, r, p;
	vector<int> used((max - min), 0);
	
	//Init
	r = 1;
	p = 0;
	
	//Get Prime Numbers out of range
	for(i = min; i < max; i++) {
		if(i != 1 && IamLupo::Prime::is(primes, i)) {
			used[p] = 1;
			p++;
			
			r *= i;
		} else {
			vector<int> result(p, 0);
			
			//Init
			v = i;
			
			id = findPrimeFactorId(v);
			while(id != -1) {
				result[id]++;
				
				v /= primes[id];
				
				if(result[id] > used[id]) {
					r *= primes[id];
					used[id]++;
				}
				
				id = findPrimeFactorId(v);
			}
			
			r *= v;
		}
	}
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(100);
	
	//232792560 = 2 * 3 * 2 * 5 * 7 * 2 * 3 * 11 * 13 * 17 * 19 * 2
	cout << "result = " << smallestOfRange(1, 20) << endl;
	
	return 0;
}
