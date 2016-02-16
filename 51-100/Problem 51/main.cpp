#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "number.h"
#include "prime.h"

using namespace std;

/*
	Find the smallest prime which, by replacing part of the number
	(not necessarily adjacent digits) with the same digit,
	is part of an eight prime value family.
*/

static IamLupo::Primes primes;

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
		t = IamLupo::Number::toVector(primes[i]);
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
					
					z = IamLupo::Number::toNumber(t2);
					if(IamLupo::Prime::isPrime(primes, z) && z >= pow(10, l - 1))
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
	IamLupo::Prime::generate(primes, 1000);

	cout << "result = " << findSmallestFamily(8, 6) << endl;
	
	return 0;
}