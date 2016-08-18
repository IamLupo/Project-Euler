#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/number.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	How many distinct sets containing each of the digits one through
	nine exactly once contain only prime elements?
*/

static IamLupo::Primes primes;

int find(const vector<int> &n, int p) {
	int i, r, v;
	vector<int> l;
	
	//Init
	r = 0;
	
	for(i = n.size() - 1; i >= 0; i--) {
		l = n;
		l.erase(l.begin(), l.begin() + i);
		
		//Generate number
		v = IamLupo::Number::to(l);
		
		if(IamLupo::Prime::is(primes, v) && v > p) {
			//Remove numbers that has been used to generate prime number
			vector<int> n2(n.begin(), n.begin() + i);
			
			//No numbers to generate primes
			if(n2.size() == 0)
				r++; //Found a solution
			else
				//Count all next level possebilities
				r += find(n2, v);
		}
	}
	
	return r;
}

int f() {
	int r;
	vector<int> v;
	
	//Init
	r = 0;
	v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	//Generate all possible Pandigital numbers
	do {
		//Find all possible Pandigital prime sets 
		r += find(v, 0);
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(10000);
	
	cout << "Result = " << f() << endl;
	
	return 0;
}
