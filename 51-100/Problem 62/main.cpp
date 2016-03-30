#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

using namespace std;

/*
	Find the smallest cube for which exactly five
	permutations of its digits are cube.
*/

int countOptions(const string &s) {
	int i, c;
	mpz_t t, min, max;
	string r;
	
	//Init
	mpz_init_set_ui(t, 0);
	mpz_init(min);
	mpz_init(max);
	c = 0;
	
	//Calculate Limits
	mpz_ui_pow_ui(min, 10, s.size() - 1);
	mpz_ui_pow_ui(max, 10, s.size());
	
	for(i = 2; mpz_cmp(t, max) < 0; i++) {
		mpz_ui_pow_ui(t, i, 3);
		
		if(mpz_cmp(t, min) >= 0) {
			// Convert and Sort
			r = mpz_get_str(NULL, 10, t);
			sort(r.begin(), r.end());
			
			if(s.compare(r) == 0)
				c++;
		}
	}
	
	return c;
}

string findSmallestCube(int l) {
	int i;
	mpz_t t;
	string v;
	
	//Init
	mpz_init(t);
	
	for(i = 2; i < 1000000; i++) {
		mpz_ui_pow_ui(t, i, 3);
		
		// Convert and Sort
		v = mpz_get_str(NULL, 10, t);
		sort(v.begin(), v.end());
	
		if(countOptions(v) >= l)
			return mpz_get_str(NULL, 10, t);
	}
	
	v.clear();
	
	return v;
}

int main() {
	cout << "result = " << findSmallestCube(5) << endl;
	
	return 0;
}