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
	Find the smallest cube for which exactly five permutations of its digits are cube.
*/

string findSmallestCube(int l) {
	int i;
	mpz_t v;
	string s;
	vector<string> r;
	
	//Init
	mpz_init(v);
	
	for(i = 1; i <= 10000; i++) {
		mpz_ui_pow_ui(v, i, 3);
		
		s = mpz_get_str(NULL, 10, v);
		sort(s.begin(), s.end());
		
		r.push_back(s);
	}
	
	for(i = 0; i < r.size(); i++) {
		if(count(r.begin(), r.end(), r[i]) >= l) {
			mpz_ui_pow_ui(v, i + 1, 3);
			
			return mpz_get_str(NULL, 10, v);
		}
	}
	
	return "";
}

int main() {
	//cout << "result = " << findSmallestCube(3) << endl;
	
	cout << "result = " << findSmallestCube(5) << endl;
	
	return 0;
}