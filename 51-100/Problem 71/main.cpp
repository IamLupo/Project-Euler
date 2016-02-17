#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order
	of size, find the numerator of the fraction immediately to the left of 3/7.
*/

int getFractionNumerator(int l) {
	int i, j, r;
	double hi, lo, t;
	
	hi = 3.0 / 7.0;
	lo = 0.0;
	r = 0;
	
	j = 0;
	for(i = 1; i <= l; i++) {
		do {
			j++;
			t = (double)j / i;
			
			if(t > lo && t < hi) {
				lo = t;
				r = j;
			}
		}
		while(t < hi);
		j--;
	}
	
	return r;
}

int main() {
	cout << "result = " << getFractionNumerator(1000000) << endl;
	
	return 0;
}