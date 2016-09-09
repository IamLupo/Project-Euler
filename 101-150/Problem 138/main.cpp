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
	Find ∑ L for the twelve smallest isosceles triangles for which h = b ± 1 and b,
	L are positive integers.
*/

/*
	Conclusion A:
		Data:
			b    L    h
			16   17   15
			272  305  273
		
		We know that h can be:
			h = b + 1
			h = b - 1
		
		After that we know that
			L = √(h^2 + (b/2)^2)
			
		We can bruteforce B to generate h and check L is a square root
			
	Conclusion B:
		After we done some brute forcing we generate the first 6 triangles with length L.
		
		Data:
			17
			305
			5473
			98209
			1762289
			31622993
		
		With a little playing we can figure this out. 
		
		T^k in kth in the Triangle results.
		
		T^k = (T^(k-1) * 18) - T^(k-2)
		
		Prove:
			T^3 = (T^2 * 18) - T^1 = (305 * 18) - 17 = 5473
*/

void bruteforce() {
	int b, h;
	mpz_t x, y;
	
	//Init
	mpz_init(x);
	mpz_init(y);
	
	for(b = 2; b < 100000000; b += 2) {
		//x = (b + 1)^2 + (b / 2)^2
		mpz_set_ui(x, b + 1);
		mpz_pow_ui(x, x, 2);
		mpz_set_ui(y, b / 2);
		mpz_pow_ui(y, y, 2);
		mpz_add(x, x, y);
		
		if(mpz_root(x, x, 2))
			cout << mpz_get_str(nullptr, 10, x) << endl;
		
		//x = (b - 1)^2 + (b / 2)^2
		mpz_set_ui(x, b - 1);
		mpz_pow_ui(x, x, 2);
		mpz_set_ui(y, b / 2);
		mpz_pow_ui(y, y, 2);
		mpz_add(x, x, y);
		
		if(mpz_root(x, x, 2))
			cout << mpz_get_str(nullptr, 10, x) << endl;
	}
}

long long f(int l) {
	int i;
	long long a, b, t, r;
	
	//Init
	a = 1;
	b = 1;
	r = 0;
	
	for(i = 0; i < l; i++) {
		t = a;
		a = b;
		b = (b * 18) - t;
		
		//Add ∑ L
		r += b;
	}
	
	return r;
}

int main() {
	cout << "Result = " << f(12) << endl;
	
	return 0;
}
