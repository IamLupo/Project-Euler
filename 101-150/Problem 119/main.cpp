#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/number.h"

using namespace std;

/*
	You are given that a2 = 512 and a10 = 614656. Find a30.
*/

int sum_digit(mpz_t v) {
	int i, r;
	string s;
	
	//Init
	r = 0;
	s = mpz_get_str(nullptr, 10, v);
	
	for(i = 0; i < s.size(); i++)
		r += IamLupo::Number::to(s.substr(i, 1));
	
	return r;
}

unsigned long long f(int n) {
	int i, j, x;
	mpz_t v;
	vector<unsigned long long> l;
	
	//Init
	mpz_init(v);
	
	for(i = 2; i <= 71; i++)
		for(j = 2; j <= 10; j++) {
			mpz_ui_pow_ui(v, i, j);
			
			if(i == sum_digit(v)) {
				//Store result
				l.push_back(mpz_get_ui(v));
				
				//Debug
				//cout << i << "^" << j << " = " << mpz_get_str(nullptr, 10, v) << endl;
			}
		}
	
	//Sort results
	sort(l.begin(), l.end());
	
	return l[n - 1];
}

int main() {
	cout << "Result = " << f(30) << endl;
	
	return 0;
}
