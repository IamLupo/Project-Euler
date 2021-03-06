#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	If the product of these four fractions is given in its lowest common terms,
	find the value of the denominator.
*/

int findDenominator() {
	int a, b, i, j, k;
	
	//Init
	a = 1;
	b = 1;
	 
	for(i = 1; i < 10; i++) {
		for(j = 1; j < i; j++) {
			for(k = 1; k < j; k++) {
				if ((k * 10 + i) * j == k * (i * 10 + j)) {
					a *= j;
					b *= k;
				}
			}
		}
	}
	
	//Get denominator
	a /= IamLupo::Math::gcd(b, a);
	
	return a;
}

int main() {
	cout << "result = " << findDenominator() << endl;
	
	return 0;
}