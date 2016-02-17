#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"
#include "IamLupo/math.h"

using namespace std;

/*
	How many chains, with a starting number below one million,
	contain exactly sixty non-repeating terms?
*/

static vector<int> factorial = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

/*
	Example:
		f(145) = 1! + 4! + 5! = 1 + 24 + 120 = 145
*/
long long algorithem(long long n) {
	int i;
	long long r;
	vector<int> v;
	
	r = 0;
	v = IamLupo::Vector::to(n);
	
	for(i = 0; i < v.size(); i++)
		r += factorial[v[i]];
	
	return r;
}

int countChains(int l, int m) {
	int i, j, r;
	long long v;
	vector<long long> t;
	vector<long long>::iterator it;
	
	r = 0;
	
	for(i = 1; i < l; i++) {
		v = i;
		t.clear();
		t.push_back(v);
		
		for(j = 0; j < m; j++) {
			v = algorithem(v);
			it = find(t.begin(), t.end(), v);
			
			if(it != t.end())
				break;
			
			t.push_back(v);
		}
		
		if(j + 1 == m) {
			r++;
			cout << i << endl;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << countChains(1000000, 60) << endl;

	return 0;
}