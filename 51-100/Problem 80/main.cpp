#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"

#include "IamLupo/number.h"

using namespace std;

/*
	For the first one hundred natural numbers, find the total of the digital sums
	of the first one hundred decimal digits for all the irrational square roots.
*/

int sumSqrtDigits(int n) {
	vector<int> r;
	mpf_t v;
	string s;
	mp_exp_t n_exp;
	
	mpf_init2(v, 1024);
	mpf_sqrt_ui(v, n);
	s = mpf_get_str(nullptr, &n_exp, 10, 102, v);
	
	return IamLupo::Number::sum(s.substr(0, 100));
}

int sumRangeSqrtDigits(int l) {
	int i, t, v, r;
	
	i = 1;
	r = 0;
	
	while(i < l) {
		t = sqrt(i);
		
		if(t * t != i)
			r += sumSqrtDigits(i);
		
		i++;
	}
	
	return r;
}

int main() {
	cout << "result = " << sumRangeSqrtDigits(100) << endl;
	
	return 0;
}
