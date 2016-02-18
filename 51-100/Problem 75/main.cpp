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
	long long a, b, c, m, n, k, t, v;
	vector<long long> once, multiple;
	vector<long long>::iterator it;
	
	for(n = 1; 2 * (n + 1) * ((n + 1) + n) <= l; n++) {
		for(m = n + 1; 2 * m * (m + n) <= l; m++) {
			if(IamLupo::Math::gcd(m, n) == 1 && (m - n) % 2 == 1) {
				t = 2 * m * (m + n);

				for(k = 1; t * k <= l; k++) {
					v = t * k;
					
					if(v <= l) {
						it = find(multiple.begin(), multiple.end(), v);
						if(it == multiple.end()) {
							it = find(once.begin(), once.end(), v);
							
							//Add
							if(it == once.end()) {
								once.push_back(v);
							} else { // Remove and Add
								//Remove
								once.erase(it);
								
								//Add
								multiple.push_back(v);
							}
						}
					}
				}
			}
		}
		cout << "Progress(611 / " << n << ") = " << once.size() << endl;
	}
	
	return once.size();
}

int main() {
	cout << "result = " << countUniqueTriangleSideLength(1500000) << endl;

	return 0;
}