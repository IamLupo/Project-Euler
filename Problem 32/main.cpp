#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	Find the sum of all products whose multiplicand/multiplier/product identity
	can be written as a 1 through 9 pandigital.
	
	Example of a pandigital:
		39 × 186 = 7254
*/

int sumProductPandigital(vector<int> s) {
	int i, a, b, c, d;
	vector<int>::iterator it;
	vector<int> l, r;
	
	//Generate range
	for(i = s[0]; i <= s[1]; i++)
		l.push_back(i);
	
	//Find pandigital
	do {
		a = l[0] * 10 + l[1];
		b = (l[2] * 100) + (l[3] * 10) + l[4];
		c = (l[1] * 1000) + (l[2] * 100) + (l[3] * 10) + l[4];
		d = (l[5] * 1000) + (l[6] * 100) + (l[7] * 10) + l[8];
		
		if(a * b == d || l[0] * c == d) {
			//Look if the product has been added before
			it = find(r.begin(), r.end(), d);
			if(it == r.end())
				r.push_back(d);
		}
		
	} while(next_permutation(l.begin(), l.end()));
	
	//Sum all the products
	return accumulate(r.begin(), r.end(), 0);;
}

int main() {
	cout << "result = " << sumProductPandigital({1, 9}) << endl;
	
	return 0;
}