#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "IamLupo/math.h"
#include "IamLupo/prime.h"
#include "IamLupo/triangular.h"

using namespace std;

/*
	What is ∑ s(n) for 1 ≤ n ≤ 10^8?
	
	Reference:
		https://oeis.org/A132994
*/

long long f(long long l) {
	long long a, b, i, n, s, v, v2, t, r;
	
	//Init
	s = l / 2;
	
	/*
		one is always a divider of all numbers in the range		l
		half of the numbers will only be a divider once			T(l) - T(l / 2)
	*/
	r = IamLupo::Triangular::get(l) - IamLupo::Triangular::get(s) + l;
	
	// Left over range
	for(n = 2; n <= s; n++)
		r += (l / n) * n;
	
	// Get imaginary divisers
	
	// a == b
	for(n = 2; n <= l; n += 2)
		r += (l / n) * n;
	
	// a != b
	for(a = 1; a * a < l; a++)
		for(b = 1; b < a; b++)
			if(IamLupo::Math::gcd(a, b) == 1) {
				v = (a * a) + (b * b);
				v2 = (a + b) * 2;
				
				for(i = 1; v * i <= l; i++) {
					t = l / (v * i);
					
					r += i * v2 * t;
				}
			}
	
	return r;
}

int main() {
	cout << "Result = " << f(100000000) << endl;
	
	return 0;
}
