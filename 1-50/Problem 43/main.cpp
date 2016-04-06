#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	Find the sum of all 0 to 9 pandigital numbers with this property.
*/

long long sumPandigital() {
	long long r;
	vector<int> v;
	
	//Init
	r = 0;
	v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	do {
		if( (v[1]*100 + v[2]*10 + v[3]) % 2 == 0 &&
			(v[2]*100 + v[3]*10 + v[4]) % 3 == 0 &&
			(v[3]*100 + v[4]*10 + v[5]) % 5 == 0 &&
			(v[4]*100 + v[5]*10 + v[6]) % 7 == 0 &&
			(v[5]*100 + v[6]*10 + v[7]) % 11 == 0 &&
			(v[6]*100 + v[7]*10 + v[8]) % 13 == 0 &&
			(v[7]*100 + v[8]*10 + v[9]) % 17 == 0)
				r += v[0] * pow(10, 9) +
					 v[1] * pow(10, 8) +
					 v[2] * pow(10, 7) +
					 v[3] * pow(10, 6) +
					 v[4] * pow(10, 5) +
					 v[5] * pow(10, 4) +
					 v[6] * pow(10, 3) +
					 v[7] * pow(10, 2) +
					 v[8] * pow(10, 1) +
					 v[9] * pow(10, 0);
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	cout << "result = " << sumPandigital() << endl;
	
	return 0;
}