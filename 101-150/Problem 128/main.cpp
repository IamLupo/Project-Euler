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
	Find the 2000th tile in this sequence.
*/

static IamLupo::Primes primes;

struct Tile {
	long long n;         // Value
	vector<long long> v; // Nabours
};

/*
	Example:
		PD({8, {20, 37, 19, 2, 9, 21}}) = 3

		The differences are 12, 29, 11, 6, 1, and 13. Three of those are prime.
*/
int PD(const Tile &t) {
	int i, r;
	long long x;
	
	//Init
	r = 0;
	
	for(i = 0; i < t.v.size(); i++) {
		x = (t.v[i] > t.n ? t.v[i] - t.n : t.n - t.v[i]);
		
		if(IamLupo::Prime::is(primes, x))
			r++;
	}
	
	return r;
}

void next(Tile &t) {
	long long d;
	
	//Init
	d = t.v[4] - t.n;
	
	t = {
		t.v[4],
		{
			t.v[3],
			t.n,
			t.v[5],
			(t.n % 2 == 0) ? t.v[3] + d + 6 : t.v[3] + d - 6,
			t.v[4] + d + 6,
			(t.n % 2 == 0) ? t.v[5] + d + 12 : t.v[5] + d + 6,
		}
	};
}

long long f(int l) {
	int r;
	Tile t1, t2;
	
	//Init
	r = 1; // we skip 1 because PD(1) = 3
	t1 = {2, {3, 1, 7, 9, 8, 19}};
	t2 = {7, {1, 6, 17, 2, 19, 18}};

	while(true) {
		if(PD(t1) == 3) {
			r++;
			
			if(r == l)
				return t1.n;
		}
		
		if(PD(t2) == 3) {
			r++;
			
			if(r == l)
				return t2.n;
		}
		
		//Calculate next Tiles
		next(t1);
		next(t2);
	}
	
	return -1;
}

int main() {
	primes = IamLupo::Prime::generate(13000);
	
	cout << "Result = " << f(2000) << endl;
	
	return 0;
}
