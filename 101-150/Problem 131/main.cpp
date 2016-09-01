#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	How many primes below one million have this remarkable property?
*/

/*
	Formula:
		y^3 = x^3 + (x^2 * p) 
	
	Data:
		1^3 + (1^2 * 7) = 2^3
		8^3 + (8^2 * 19) = 12^3
		27^3 + (27^2 * 37) = 36^3
		64^3 + (64^2 * 61) = 80^3
		216^3 + (216^2 * 127) = 252^3
		729^3 + (729^2 * 271) = 810^3
		1000^3 + (1000^2 * 331) = 1100^3
		1331^3 + (1331^2 * 397) = 1452^3
		2197^3 + (2197^2 * 547) = 2366^3
		2744^3 + (2744^2 * 631) = 2940^3
		4913^3 + (4913^2 * 919) = 5202^3
		12167^3 + (12167^2 * 1657) = 12696^3
	
	Conclusion:
		Step 1: Separate x^3
			y^3 = x^3(1 + (p / x))
		
		Step 2: convert 1 to x / x
			y^3 = x^3((x / x) + (p / x))
		
		Step 3: Re-arrange
			y^3 = x^3((p + x) / x)
		
		Step 4: Remove cube
			y = x * 3√((p + x) / x)
		
		Step 5: Separate division in two cubes
			y = x * (3√(p + x) / 3√(x))
			
		Step 6:
			We know now that "x" and "p + x" must be a cube number.
		
			a^3 = p + x
			b^3 = x
			
			a^3 = p + b^3
			p = a^3 - b^3
		
		Step 7: Pascal triangle
			p = (a - b)(a^2 + ab + b^2)
			
			We see that a - b must be a divider of our prime number.
			Basic knowledge tells us that a prime number can only divide by 1 or itself.
			
		Step 8: Finish
			a - b = 1
			
			p = a^3 - (a - 1)^3
*/

static IamLupo::Primes primes;

void draw(int a, int p) {
	long long x;
	mpz_t x1, x2, y;
	
	//Init
	mpz_init(x1);
	mpz_init(x2);
	mpz_init(y);
	
	//Calculate x
	x = pow(a - 1, 3);
			
	//x1 = x^3
	mpz_ui_pow_ui(x1, x, 3);
	
	//x2 = x^2 * p
	mpz_ui_pow_ui(x2, x, 2);
	mpz_mul_ui(x2, x2, p);
	
	//y^3 = x1 + x2
	mpz_add(y, x1, x2);
	mpz_root(y, y, 3);
	
	//Debug
	cout << x << "^3 + (" << x << "^2 * " << p << ") = " << mpz_get_str(nullptr, 10, y) << "^3" << endl;
	
	mpz_clear(x1);
	mpz_clear(x2);
	mpz_clear(y);
}

int f(int l) {
	int a, r;
	long long d;
	
	//Init
	r = 0;
	a = 2;
	
	do {
		//Calculate distance between two cubes
		d = pow(a, 3) - pow(a - 1, 3);
	
		//Check if distance between cubes is a prime number
		if(IamLupo::Prime::is(primes, d)) {
			//Debug
			//draw(a, d);
			
			r++;
		}
		
		//Next a
		a++;
	} while(d < l);
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(10000);
	
	cout << "Result = " << f(1000000) << endl;

	return 0;
}
