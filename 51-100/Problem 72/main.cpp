#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	How many elements would be contained in the set of
	reduced proper fractions for d ≤ 1,000,000?
*/

long long countProperFractions(int l) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 2; i <= l; i++)
		r += IamLupo::Math::phi(i);
	
	return r;
}

int main() {
	cout << "result = " << countProperFractions(1000000) << endl;
	
	return 0;
}