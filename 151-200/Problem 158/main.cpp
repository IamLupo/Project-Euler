#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "gmp.h"

using namespace std;

/*
	What is the maximum value of p(n)?
*/

/*
	Formula:
		f(x) = 2^x - 1 - x
	
	Data:
		1, 1, 4, 11, 26, 57, 120, 247, 502, 1013, 2036, 
		4083, 8178, 16369, 32752, 65519, 131054, 262125,
		524268, 1048555, 2097130, 4194281, 8388584, 16777191,
		33554406, 67108837, 134217700, 268435427, 536870882,
		1073741793, 2147483616, ...
	
	Reference:
		https://oeis.org/A130103
*/
long long A130103(int v) {
	return pow(2, v) - 1 - v;
}

/*
	Formula:
		f(x) = ((!26 / !(26 - x - 1)) / !x) * A130103(x)
*/
long long f() {
	int i;
	long long r, d, v;
	mpz_t x, y;
	
	//Init
	r = 0;
	mpz_init_set_ui(x, 1);
	mpz_init(y);
	
	for(i = 1; i <= 26; i++) {
		// x = !26 / !(i - 1)
		mpz_mul_ui(x, x, 26  - i + 1);
		
		// y = !i
		mpz_fac_ui(y, i);
		
		// y = x / y
		mpz_div(y, x, y);
		
		// v = y * A130103(i)
		v = mpz_get_ui(y) * A130103(i);
		
		// Find highest
		if(v > r)
			r = v;
	}
	
	// Clear
	mpz_clear(x);
	mpz_clear(y);
	
	return r;
}

int main() {
	cout << "Result = " << f() << endl;
	
	return 0;
}
