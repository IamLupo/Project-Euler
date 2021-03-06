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
	In the first one-thousand expansions, how many fractions contain
	a numerator with more digits than denominator?
*/

int countBiggerNumeratorDigit() {
	int i, r;
	mpz_t x, y, d, a;
	string s, t;
	
	//Init
	r = 0;
	mpz_init_set_ui(x, 3);
	mpz_init_set_ui(y, 2);
	mpz_init_set_ui(d, 1);
	mpz_init(a);
	
	for(i = 0; i < 1000; i++) {
		//a = y
		mpz_set(a, y);
		
		//y += y
		mpz_add(y, y, y);
		
		//x += y
		mpz_add(x, x, y);
		
		//y += d
		mpz_add(y, y, d);
		
		//d = a
		mpz_set(d, a);
		
		//Get length of number
		s = mpz_get_str(nullptr, 10, x);
		t = mpz_get_str(nullptr, 10, y);
		
		if(s.size() > t.size())
			r++;
	}
	
	return r;
}

int main() {
	cout << "result = " << countBiggerNumeratorDigit() << endl;
	
	return 0;
}