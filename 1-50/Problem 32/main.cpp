#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

using namespace std;

/*
	Find the sum of all products whose multiplicand/multiplier/product identity
	can be written as a 1 through 9 pandigital.
	
	Example of a pandigital:
		39 × 186 = 7254
*/

int sumProductPandigital(int begin, int end) {
	int i, a, b, c, d;
	vector<int> l;
	set<int> r;
	
	//Generate range
	for(i = begin; i <= end; i++)
		l.push_back(i);
	
	//Find pandigital
	do {
		a = l[0] * 10 + l[1];
		b = (l[2] * 100) + (l[3] * 10) + l[4];
		c = (l[1] * 1000) + (l[2] * 100) + (l[3] * 10) + l[4];
		d = (l[5] * 1000) + (l[6] * 100) + (l[7] * 10) + l[8];
		
		if(a * b == d || l[0] * c == d)
			r.insert(d);
		
	} while(next_permutation(l.begin(), l.end()));
	
	//Sum all the products
	return accumulate(r.begin(), r.end(), 0);
}

int main() {
	cout << "result = " << sumProductPandigital(1, 9) << endl;
	
	return 0;
}