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
	Find the 15th golden nugget.
*/

/*
	Formula:
		AF(x) = (x * F^1) + (x^2 * F^2) + (x^3 * F^3) + ...
		
		F^k is the kth term in the Fibonacci sequence
		
	Data:
		x                   AF(x)
		(√1 − 1) / 0        0
		(√8 − 2) / 2        1
		(√25 − 3) / 4       2
		(√52 − 4) / 6       3
		(√89 − 5) / 8       4
		(√136 − 6) / 10     5
		
		I converted the "x" results in the story into a more representable version.
	
	Conclusion A: Pattern in equation
		x = (√a − b) / c

		b = AF(x) + 1
		c = AF(x) * 2
		
		Between AF(x) = 0 and AF(x) = 1 you see "a" increases by 7
		Between AF(x) = 1 and AF(x) = 2 you see "a" increases by 17
		Between AF(x) = 2 and AF(x) = 3 you see "a" increases by 27
		Between AF(x) = 3 and AF(x) = 4 you see "a" increases by 37
		Between AF(x) = 4 and AF(x) = 5 you see "a" increases by 47
		
		Basicly we will have as a initialisation state
		a = 1
		y = 7
		
		for every next result we will have
		a += y
		y += 10
	
	Conclusion B: Pattern in the Golden Nugget's
		With Conclusion A we found some Golden Nuggets,
		but after 10th nugget the algo becomes to slow
		
		N^k is the kth term in the Golden nugget sequence
		
		Data:
			N^1 = 2
			N^2 = 15
			N^3 = 104
			N^4 = 714
			N^5 = 4895
			N^6 = 33552
			N^7 = 229970
			N^8 = 1576239
			N^9 = 10803704
			N^10 = 74049690
		
		If we have the first nugget we calculate the next nugget by the following formula.
		
		N^k = N^(k-1) * 7 - N^(k-2) + 1
		
		Prove:
			N^3 = N^2 * 7 - N^1 + 1 = 15 * 7 - 2 + 1 = 104
*/

/*
	Draw first 10 Golden nuggets
*/
void draw() {
	long long x;
	
	mpz_t a, t, y;
	
	//Init
	mpz_init_set_ui(a, 8);
	mpz_init(t);
	mpz_init_set_ui(y, 17);
	
	//Debug
	cout << "Golden nuggets = ";
	
	for(x = 1; x < 74049691; x++) {
		if(mpz_root(t, a, 2)) {
			//Debug
			cout << x << ", ";
		}
		
		//Next Generation
		mpz_add(a, a, y);
		mpz_add_ui(y, y, 10);
	}
	
	cout << endl;
	
	mpz_clear(a);
	mpz_clear(t);
	mpz_clear(y);
}

long long f(int k) {
	int i;
	long long a, b, t;
	
	//Init
	a = 0;
	b = 2; // N^1
	
	for(i = 1; i < k; i++) {
		t = a;
		a = b;
		b = b * 7 - t + 1;
	}
	
	return b;
}

int main() {
	cout << "Result = " << f(15) << endl;
	
	//Debug
	//draw();
	
	return 0;
}
