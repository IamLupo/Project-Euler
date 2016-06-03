#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	Given that L is the length of the wire, for how many values of L ≤ 1,500,000
	can exactly one integer sided right angle triangle be formed?
	
	https://en.wikipedia.org/wiki/Pythagorean_theorem
	https://en.m.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
	https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples
	
	Rules:
		a = m^2 - n^2
		b = 2mn
		c = m^2 + n^2
		
		m > n, m - n odd, m and n coprime
	
	Conversion:
		L = m^2 - n^2 + 2mn + m^2 + n^2
		L = m^2 + 2mn + m^2
		L = 2m^2 + 2mn
		L = 2m(m + n)
*/

int countUniqueTriangleSideLength(int l) {
	int m, n, k, r;
	long long t, v;
	vector<long long> lst(l + 1, 0);
	
	//Init
	r = 0;
	
	for(n = 1; 2 * (n + 1) * ((n + 1) + n) <= l; n++) {
		for(m = n + 1; 2 * m * (m + n) <= l; m++) {
			if(IamLupo::Math::gcd(m, n) == 1 && (m - n) % 2 == 1) {
				t = 2 * m * (m + n);

				for(k = 1; t * k <= l; k++) {
					v = t * k;
					
					if(v <= l)
						lst[v]++;
				}
			}
		}
	}
	
	for(n = 0; n < lst.size(); n++)
		if(lst[n] == 1)
			r++;
	
	return r;
}

int main() {
	cout << "result = " << countUniqueTriangleSideLength(1500000) << endl;

	return 0;
}