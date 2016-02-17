#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	How many fractions lie between 1/3 and 1/2 in the sorted set of
	reduced proper fractions for d ≤ 12,000?
*/

long long countProperFractions(int l) {
	int i, j, r;
	double hi, lo, t;
	
	hi = 1.0 / 2.0;
	lo = 1.0 / 3.0;
	r = 0;
	
	j = 1;
	for(i = 2; i <= l; i++) {
		do {
			j++;
			t = (double)j / i;
			
			if(t > lo && t < hi && IamLupo::Math::gcd(j, i) == 1)
				r++;
		}
		while(t < hi);
		j = 1;
	}
	
	return r;
}

int main() {
	cout << "result = " << countProperFractions(12000) << endl;
	
	return 0;
}