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
	How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100,
	are greater than one-million?
*/

/*
	                 n!
	C(n, r, m) =  ---------- > m
	              r!(n - r)!
*/
bool C(int n, int r, int m) {
	int i;
	mpz_t a, b;
	char buffer[10000];
	
	//Init
	mpz_init_set_ui(a, 1);
	mpz_init_set_ui(b, 1);
	
	// !(n - r)
	for(i = n - r + 1; i <= n; i++)
		mpz_mul_ui(a, a, i);
	
	// !r
	for(i = 1; i <= r; i++)
		mpz_mul_ui(b, b, i);
	
	// a / b
	mpz_div(a, a, b);
	
	return (mpz_cmp_ui(a, m) > 0);
}

int countDistinctValues(vector<int> s, int m) {
	int i, j, v, c;
	
	c = 0;

	for(i = s[1]; i >= s[0]; i--) {
		for(j = i; j >= s[0]; j--) {
			if(C(i, j, m))
				c++;
		}
	}
	
	return c;
}

int main() {
	cout << "result = " << countDistinctValues({1, 100}, 1000000) << endl;
	
	return 0;
}