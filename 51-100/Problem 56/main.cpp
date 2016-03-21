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
	Considering natural numbers of the form, ab, where a, b < 100,
	what is the maximum digital sum?
*/

int countMaxDigits(int l) {
	int i, j, c, r;
	mpz_t a, b;
	
	//Init
	r = 0;
	mpz_init(a);
	mpz_init(b);
	
	//Add all values in list
	for(i = 1; i < l; i++) {
		mpz_set_ui(a, i);
		for(j = 1; j < l; j++) {
			// b = a^j
			mpz_pow_ui(b, a, j);
			
			//Calc the sum of digits
			c = IamLupo::Number::sum(mpz_get_str(nullptr, 10, b));
			
			//if a higher value is found save it
			if(r < c)
				r = c;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << countMaxDigits(100) << endl;
	
	return 0;
}