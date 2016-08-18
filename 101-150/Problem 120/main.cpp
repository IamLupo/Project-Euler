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
	For 3 ≤ a ≤ 1000, find ∑ r^max.
*/

/* Slow */
long long calc(int a, int n) {
	mpz_t x, y, z;
	
	//x = (a - 1)^n
	mpz_init_set_ui(x, a - 1);
	mpz_pow_ui(x, x, n);
	
	//y = (a + 1)^n
	mpz_init_set_ui(y, a + 1);
	mpz_pow_ui(y, y, n);
	
	//z = a^2
	mpz_init_set_ui(z, a);
	mpz_pow_ui(z, z, 2);
	
	//x = (x + y) % z
	mpz_add(x, x, y);
	mpz_mod(x, x, z);
	
	return mpz_get_ui(x);
}

long long f2(int min, int max) {
	int i, j;
	long long h, v, r;
	
	//Init
	r = 0;
	
	for(i = min; i <= max; i++){
		for(j = 1; j <= i * 2; j++) {
			v = calc(i, j);
			
			if(h < v)
				h = v;
		}
		
		r += h;
		
		cout << h << ", ";
	}
	
	cout << endl;
	
	return r;
}

/* Fast */
/*
	if (n % 2, n^2 - n, n^2 - 2*n)
	
	Reference:
		http://oeis.org/A159469
*/
long long f(int min, int max) {
	int i;
	long long r;
	
	//Init
	r = 0;
	
	for(i = min; i <= max; i++) {
		r += pow(i, 2) - i;
		
		if(i % 2 == 0)
			r -= i;
	}
	
	return r;
}


int main() {
	cout << "Result = " << f(3, 1000) << endl;
	
	return 0;
}
