#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
	Find ∑mdrs(n) for 1 < n < 1,000,000.
*/

int sum(int x) {
	int r;
	
	//Init
	r = 0;
	
	while (x > 0) {
		r += x % 10;
		x /= 10;
	}

	if (r >= 10)
		r = sum(r);
	
	return r;
}

long long f(int l) {
	int i, j, v;
	vector<int> mdrs;
	
	//Init
	mdrs.resize(l, 0);
	
	// Find
	for(i = 0; i < mdrs.size(); i++)
		mdrs[i] = sum(i);
	
	for(i = 2; i * i < l; i++)
		for(j = i; i * j < l; j++)
			if(mdrs[i * j] < mdrs[i] + mdrs[j])
				mdrs[i * j] = mdrs[i] + mdrs[j];
	
	return accumulate(mdrs.begin() + 2, mdrs.end(), 0);
}

int main() {
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
