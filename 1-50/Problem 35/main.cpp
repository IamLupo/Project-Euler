#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/prime.h"
#include "IamLupo/vector.h"
#include "IamLupo/number.h"

using namespace std;

/*
	How many circular primes are there below one million?
*/

static IamLupo::Primes primes;

int countCircularPrimes() {
	int i, j, k, t;
	vector<int> v;
	set<int> l, l2;
	bool f;
	
	for(i = 0; i < primes.size(); i++) {
		v = IamLupo::Vector::to(primes[i]);
		reverse(v.begin(), v.end());
		
		l2.clear();
		
		/*
			Circular primes has v size possebilities
			Example: 197, 971, and 719
		*/
		f = true;
		for(j = 0; j < v.size() && f; j++) {
			v.push_back(v[0]);
			v.erase(v.begin());
			t = IamLupo::Number::to(v);
			
			//Check if prime
			if(!IamLupo::Prime::is(primes, t))
				f = false;
			
			l2.insert(t);
		}
		
		//If no mistakes where made update the main list with new results
		if(f)
			l.insert(l2.begin(), l2.end());
	}
	
	//Count results
	return l.size();
}

int main() {
	primes = IamLupo::Prime::readFile(1000000);
	
	cout << "result = " << countCircularPrimes() << endl;
	
	return 0;
}