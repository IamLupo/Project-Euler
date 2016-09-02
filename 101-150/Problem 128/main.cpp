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
		PD(8, {20, 37, 19, 2, 9, 21}) = 3

		The differences are 12, 29, 11, 6, 1, and 13. Three of those are prime.
*/
int PD(long long n, vector<long long> &v) {
	int i, r;
	long long t;
	
	//Init
	r = 0;
	
	for(i = 0; i < v.size(); i++) {
		t = (v[i] > n ? v[i] - n : n - v[i]);
		
		if(IamLupo::Prime::is(primes, t))
			r++;
	}
	
	return r;
}

void next(Tile &t) {
	long long d;
	
	d = t.v[4] - t.n;
	
	t.v[0] = t.v[3];
	t.v[1] = t.n;
	t.v[2] = t.v[5];
	
	t.n = t.v[4];
	
	// Left Tile
	if(t.n % 2 == 0) {
		t.v[3] += d + 6;
		t.v[4] += d + 6;
		t.v[5] += d + 12;
	}
	else
	{ // Right Tile
		t.v[3] += d - 6;
		t.v[4] += d + 6;
		t.v[5] += d + 6;
	}
}

long long f(int l) {
	int r;
	Tile t1, t2;
	
	//Init
	r = 1; // we skip 1 because PD(1) = 3 
	
	t1.n = 2;
	t1.v = {3, 1, 7, 9, 8, 19};
	
	t2.n = 7;
	t2.v = {1, 6, 17, 2, 19, 18};

	while(true) {
		if(PD(t1.n, t1.v) == 3) {
			r++;
			
			//Debug
			//cout << t1.n << endl;
			
			if(r == l)
				return t1.n;
		}
		next(t1);
		
		if(PD(t2.n, t2.v) == 3) {
			r++;
			
			//Debug
			//cout << t2.n << endl;
			
			if(r == l)
				return t2.n;
		}
		
		next(t2);
	}
	
	return -1;
}

int main() {
	primes = IamLupo::Prime::generate(13000);
	
	cout << "Result = " << f(2000) << endl;
	
	return 0;
}