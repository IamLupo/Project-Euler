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
	Given that Fk is the first Fibonacci number for which the first nine digits AND
	the last nine digits are 1-9 pandigital, find k.
*/
static string pandigital = "123456789";

bool isPandigital(const string &s) {
	string t;
	
	//Init
	t = s;
	
	sort(t.begin(), t.end());
	
	return t == pandigital;
}

int f() {
	int i;
	long long x1, y1, z1; // Faster way to get the last part of the Fibonacci number
	mpz_t x2, y2, z2;     // Generate full Fibonacci number
	string s;
	
	//Init
	x1 = 1;
	y1 = 1;
	mpz_init_set_ui(x2, 1);
	mpz_init_set_ui(y2, 1);
	mpz_init(z2);
	
	for(i = 1; i < 1000000; i++) {
		// z = y
		mpz_set(z2, y2);
		z1 = y1;
		
		// y = x + y
		mpz_add(y2, x2, y2);
		y1 = (y1 + x1) % 1000000000;
		
		// x = z
		mpz_set(x2, z2);
		x1 = z1;
		
		//Convert to String
		s = to_string(x1);
		
		//Check last part of Fibonacci number
		if(s.size() >= 9 && isPandigital(s)) {
			//Convert to String
			s = mpz_get_str(nullptr, 10, x2);
			
			if(isPandigital(s.substr(0, 9)))
				return i + 1;
		}
	}
	
	return -1; // Unknown
}

int main() {
	cout << "Result = " << f() << endl;
	
	return 0;
}
