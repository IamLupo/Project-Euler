#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdio.h>

#include "gmp.h"

using namespace std;

/*
	Find the sum of digits in the numerator of the
	100th convergent of the continued fraction for e.
*/

int add(string s) {
	int i, v, r;
	
	r = 0;
	
	for(i = 0; i < s.size(); i++)
		r += s[i] - 48;
	
	return r;
}

vector<string> getHenceSequence(const vector<int> &v, int l) {
	int i, vl, id, r;
	mpz_t x1, x2, y1, y2, t;
	
	//Init
	mpz_init_set_ui(x1, 1);
	mpz_init_set_ui(x2, v[0]);
	
	mpz_init_set_ui(y1, 0);
	mpz_init_set_ui(y2, 1);
	mpz_init(t);
	
	id = 0;
	vl = v.size() - 1;
	
	for(i = 1; i < l; i++) {
		//Generate x
		//t = x2
		mpz_set(t, x2);
		
		mpz_mul_ui(x2, x2, v[id + 1]);
		mpz_add(x2, x2, x1);
		
		//y1 = t
		mpz_set(x1, t);
		
		//Generate y
		//t = y2
		mpz_set(t, y2);
		
		//y2 = (y2 * v) + y1
		mpz_mul_ui(y2, y2, v[id + 1]);
		mpz_add(y2, y2, y1);
		
		//y1 = t
		mpz_set(y1, t);
		
		//Next id
		id = (id + 1) % vl;
	}
	
	return {mpz_get_str(nullptr, 10, x2), mpz_get_str(nullptr, 10, y2)};
}

vector<int> genPattern(int l) {
	int n;
	vector<int> r;
	
	n = 2;
	r.push_back(2);
	
	while(r.size() < l) {
		r.push_back(1);
		r.push_back(n);
		r.push_back(1);
		
		n += 2;
	}
	
	return r;
}

int sumDigitsNumerator(int l) {
	vector<string> r;
	vector<int> e;
	
	e = genPattern(l);
	r = getHenceSequence(e, l);
	
	return add(r[0]);
}

int main() {
	cout << "result = " << sumDigitsNumerator(100) << endl;
	
	return 0;
}