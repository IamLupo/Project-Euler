#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	Find the sum of all 0 to 9 pandigital numbers with this property.
*/

long long toLongLong(vector<int> &v) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i] * pow(10, i);
	
	return r;
}

long long sumPandigital() {
	int i, j, t;
	long long r;
	vector<int> v, c;
	bool f;
	
	r = 0;
	c = { 2, 3, 5, 7, 11, 13, 17 };
	
	//Generate number
	for(i = 0; i <= 9; i++)
		v.push_back(i);
	
	do {
		f = true;
		
		for(i = 0; i < 7 && f; i++) {
			vector<int> v2(v.end() - i - 4, v.end() - i - 1);
			
			if(toLongLong(v2) % c[i] != 0)
				f = false;
		}
		
		if(f)
			r += toLongLong(v);
		
	} while(next_permutation(v.begin(), v.end()));
	
	return r;
}

int main() {
	cout << "result = " << sumPandigital() << endl;
	
	return 0;
}