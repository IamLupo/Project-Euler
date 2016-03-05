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
	Consider the following tenth degree polynomial generating function:

	u^n = 1 − n + n^2 − n^3 + n^4 − n^5 + n^6 − n^7 + n^8 − n^9 + n^10

	Find the sum of FITs for the BOPs.
*/

/*
	Data:
		f(1) = 1
		f(2) = 683
		f(3) = 44287
		f(4) = 838861
		f(5) = 8138021
		f(6) = 51828151
		f(7) = 247165843
		f(8) = 954437177
		f(9) = 3138105961
		
		OP(1, n) = 1				1, (1),
		OP(2, n) = 682n − 681		1, 683, (1365),
		OP(3, n) = 					1, 683, 44287, (?),
		
	Conclusion
		f(2):
			distance({1, 683}) = 682
			683 + 682 = 1365
		
		f(3):
			distance({1, 683, 44287}) = distance({682, 43604}) = 42922
			43604 + 42922 = 86526
*/

/*
	f(n) = 1 − n + n^2 − n^3 + n^4 − n^5 + n^6 − n^7 + n^8 − n^9 + n^10
	f(n) = 1 - (n + n^3 + n^5 + n^7 + n^9) * (n - 1)
*/
long long f(long long n) {
	return 1 + ((n + pow(n, 3) + pow(n, 5) + pow(n, 7) + pow(n, 9)) * (n - 1));
}

long long distance(const vector<long long> &v) {
	int i;
	vector<long long> n;
	
	for(i = 0; i < v.size() - 1; i++)
		n.push_back(v[i + 1] - v[i]);
	
	if(n.size() == 1)
		return n[0];
	else
		return n[n.size() - 1] + distance(n);
}

long long sum(long long int (*func)(long long int)) {
	long long i, t, r, d;
	vector<long long> v;
	
	r = 0;
	d = 0;
	t = func(1);
	v.push_back(t);
	
	for(i = 2; t + d != func(i); i++) {
		r += t + d;
		t = func(i);
		v.push_back(t);
		d = distance(v);
	}
	
	return r;
}

int main() {
	cout << "result = " << sum(f) << endl;
	
	return 0;
}
