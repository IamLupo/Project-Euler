#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	Find the sum of all numbers which are equal to the sum of the factorial of their digits.
*/

static vector<int> options = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

int sumFractorial() {
	int i, j, v, r;

	r = 0;
	
	for(i = 10; i < 50000; i++) {
		v = 0;
		
		for(j = i; j > 0; j /= 10)
			v += options[j % 10];
		
		if(v == i)
			r += v;
	}
	
	return r;
}

int main() {
	cout << "result = " << sumFractorial() << endl;
	
	return 0;
}