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
	T(285) = P(165) = H(143) = 40755.
	Find the next triangle number that is also pentagonal and hexagonal.
*/

long long H(long long v) {
	return ((v * 2) - 1) * v;
}

long long next(const vector<long long> &v) {
	long long a, b, c;
	vector<long long> r;
	
	//Init
	r = v;
	
	//Next
	r[0]++;
	
	while(1) {
		a = (r[0] + 1) * r[0];				// Triangle
		b = ((r[1] * 3) - 1) * r[1];		// Pentagonal
		
		if(a < b)
			r[0]++;
		else if(a > b)
			r[1]++;
		else {
			c = ((r[2] * 4) - 2) * r[2];	// Hexagonal
			
			if(c < a)
				r[2]++;
			else if(c > a)
				r[0]++;
			else
				break;
		}
	}
	
	return H(r[2]);
}

int main() {
	cout << "result = " << next({285, 143, 143}) << endl;
	
	return 0;
}