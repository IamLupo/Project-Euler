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
	Find the smallest member of the longest amicable chain with no element
	exceeding one million.
*/

int sumDividers(int v) {
	int i, d, r;
	
	if(v == 4)
		return 3;
	
	r = 1;
	d = v / 2;
	
	for(i = 2; i < d; i++) {
		if(v % i == 0) {
			d = v / i;
			r += i;
			
			if(i != d)
				r += d;
		}
	}
	
	return r;
}

int main() {
	int i;
	
	for(i = 1; i < 1000000; i++)
		cout << sumDividers(i) << endl;
	
	return 0;
}
