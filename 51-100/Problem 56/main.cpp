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
	Considering natural numbers of the form, ab, where a, b < 100,
	what is the maximum digital sum?
*/

int countMaxDigits(int l) {
	int i, j, c, h;
	mpz_t a, b;
	char buffer[10000];
	
	//Init
	h = 0;
	mpz_init(a);
	mpz_init(b);
	
	//Add all values in list
	for(i = 1; i < l; i++) {
		mpz_set_ui(a, i);
		for(j = 1; j < l; j++) {
			// a^b
			mpz_pow_ui(b, a, j);
			
			//Get result
			mpz_get_str(buffer, 10, b);
			
			//Calc the sum of digits
			c = IamLupo::Number::sum(buffer);
			
			//if a higher value is found save it
			if(h < c)
				h = c;
		}
	}
	
	return h;
}

int main() {
	cout << "result = " << countMaxDigits(100) << endl;
	
	return 0;
}