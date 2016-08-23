#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/math.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	Find the least value of n for which A(n) first exceeds one-million.
*/	

/*
	A(n) = lowest k in R(k) % n == 0
	
	n is a positive integer and GCD(n, 10) = 1
	means n can be a number that starts with 1, 3, 7 and 9
	
	Example 1:
		R(6) = 111111
		
		because R(6) is the lowest value it can be divided by 7 that makes A(7) = 6
	
	Data:
		A(1) = 1
		{0, }
		
		A(3) = 3
		{1, 2, 0, }
		
		A(7) = 6
		{1, 4, 6, 5, 2, 0, }
		
		A(9) = 9
		{1, 2, 3, 4, 5, 6, 7, 8, 0, }
		
		A(11) = 2
		{1, 0, }
		
		A(13) = 6
		{1, 11, 7, 6, 9, 0, }
		
		A(17) = 16
		{1, 11, 9, 6, 10, 16, 8, 13, 12, 2, 4, 7, 3, 14, 5, 0, }
		
		A(19) = 18
		{1, 11, 16, 9, 15, 18, 10, 6, 4, 3, 12, 7, 14, 8, 5, 13, 17, 0, }
		
		A(21) = 6
		{1, 11, 6, 19, 2, 0, }
		
		A(23) = 22
		{1, 11, 19, 7, 2, 21, 4, 18, 20, 17, 10, 9, 22, 14, 3, 8, 12, 6, 15, 13, 16, 0, }
		
		A(27) = 27
		{1, 11, 3, 4, 14, 6, 7, 17, 9, 10, 20, 12, 13, 23, 15, 16, 26, 18, 19, 2, 21, 22, 5, 24, 25, 8, 0, }
		
		A(29) = 28
		{1, 11, 24, 9, 4, 12, 5, 22, 18, 7, 13, 15, 6, 3, 2, 21, 8, 23, 28, 20, 27, 10, 14, 25, 19, 17, 26, 0, }
		
		A(31) = 15
		{1, 11, 18, 26, 13, 7, 9, 29, 12, 28, 2, 21, 25, 3, 0, }
		
		A(33) = 6
		{1, 11, 12, 22, 23, 0, }
		
		A(37) = 3
		{1, 11, 0, }
		
		A(39) = 6
		{1, 11, 33, 19, 35, 0, }
		
		A(41) = 5
		{1, 11, 29, 4, 0, }
	
	Conclusion A:
		n >= k
		
	Conclusion B:
		A(3^x) = 3^x
		
		Prove:
			A(3) = 3
			A(9) = 9
			A(27) = 27
			A(81) = 81
			A(243) = 243
			A(729) = 729
	
	Conclusion C:
		1000000 < answer < 3^12
	
	Conclusion D:
		n = 17
		v = {1, 11, 9, 6, 10, 16, 8, 13, 12, 2, 4, 7, 3, 14, 5, 0, }
		
		v[0] = 1
		v[x + 1] = (v[x] * 10) + 1 % n
		
		we stop until we reach 0
*/

static vector<int> digit = {1, 3, 7, 9};

//Generate next c
void next(mpz_t c, long long v) {
	do {
		mpz_mul_ui(c, c, 10);
		mpz_add_ui(c, c, 1);
	} while(mpz_cmp_ui(c, v) < 0);
}

vector<int> algo(int n) {
	int i;
	mpz_t c, x;
	vector<int> r;
	string s;
	
	if(n == 1)
		return {0};
	
	//Init
	mpz_init(x);
	mpz_init_set_ui(c, 1);
	
	for(i = 0; i < n; i++) {		
		//x = c % n
		mpz_mod_ui(x, c, n);
		
		//Save result
		r.push_back(mpz_get_ui(x));
		
		// Found result
		if(mpz_cmp_ui(x, 0) == 0) {
			//Clean
			mpz_clear(c);
			mpz_clear(x);
			
			return r;
		}
		
		//Next c
		next(c, 0);
	}
	
	//Clean
	mpz_clear(c);
	mpz_clear(x);
	
	return {}; // End of loop
}

/* Debugging */
void test() {
	int i, j, k, n;
	vector<int> v;
	
	for(i = 0; i < 10; i++) {
		for(j = 0; j < digit.size(); j++) {
			n = (i * 10) + digit[j];
			
			v = algo(n);
		
			cout << "A(" << n << ") = " << v.size() << endl;
			
			cout << "{";
			for(k = 0; k < v.size(); k++)
				cout << v[k] << ", ";
			cout << "}" << endl;
		}
	}
}

/* Solution */
int f(int l) {
	int i, v, n, k, c;
	
	//Init
	v = l / 10;
	
	while(true) {
		for(i = 0; i < digit.size(); i++) {
			//Generate a number
			n = (v * 10) + digit[i];
			
			//Init
			k = 1;
			c = 1;
			
			//Generate k
			while(c % n != 0) {
				c %= n;
				c *= 10;
				c += 1;
				k++;
			}
			
			//Check results
			if(k > l)
				return n;
		}
		v++;
	}
	
	return -1; // Unknown error :$
}

int main() {
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
