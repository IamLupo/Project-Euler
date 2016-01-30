#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"

using namespace std;

/*
	In the first one-thousand expansions, how many fractions contain
	a numerator with more digits than denominator?
*/

int countBiggerNumeratorDigit() {
	int i;
	long long c;
	mpz_t x, y, d, a;
	char c_x[10000], c_y[10000];
	
	//Init
	mpz_init_set_ui(x, 3);
	mpz_init_set_ui(y, 2);
	mpz_init_set_ui(d, 1);
	mpz_init(a);
	c = 0;
	
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
		mpz_get_str(c_x, 10, x);
		mpz_get_str(c_y, 10, y);
		
		if(strlen(c_x) > strlen(c_y))
			c++;
	}
	
	return c;
}

int main() {
	cout << "result = " << countBiggerNumeratorDigit() << endl;
	
	return 0;
}