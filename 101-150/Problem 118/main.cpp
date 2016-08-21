#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/number.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	How many distinct sets containing each of the digits one through
	nine exactly once contain only prime elements?
*/

static IamLupo::Primes primes;

int find(int n, int p) {
	int r, v;
	
	//Init
	r = 0;
	v = 0;
	
	while(n > 0) {
		//Generate number
		v *= 10;
		v += n % 10;
		n /= 10;
		
		if(v > p && IamLupo::Prime::is(primes, v)) {
			//No numbers to generate primes
			if(n == 0)
				r++; //Found a solution
			else
				//Count all next level possebilities
				r += find(n, v);
		}
	}
	
	return r;
}

int f() {
	int r, v;
	vector<int> l;
	
	//Init
	r = 0;
	l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	//Generate all possible Pandigital numbers
	do {
		//Convert to integer
		v = IamLupo::Number::to(l);
		
		//Find all possible Pandigital prime sets 
		r += find(v, 0);
	} while(next_permutation(l.begin(), l.end()));
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(10000);
	
	cout << "Result = " << f() << endl;
	
	return 0;
}
