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
	Find the sum of all the multiples of 3 or 5 below 1000.
*/

int sumMultiples(int nr, const vector<int> &m) {
	int i, j, r;
	
	r = 0;
	
	for(i = 0; i < nr; i++) {
		for(j = 0; j < m.size(); j++) {
			if(i % m[j] == 0) {
				r += i;
				j = m.size();
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << sumMultiples(1000, {3, 5}) << endl;
	
	return 0;
}
