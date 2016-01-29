#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	T(285) = P(165) = H(143) = 40755.
	Find the next triangle number that is also pentagonal and hexagonal.
*/

long long H(int v) {
	return ((v * 2) - 1) * v;
}

void nextTriangle(vector<long long> &v) {
	long long a, b, c;

	v[0]++;
	
	while(1) {
		a = (v[0] + 1) * v[0];
		b = ((v[1] * 3) - 1) * v[1];
		
		if(a < b)
			v[0]++;
		else if(a > b)
			v[1]++;
		else {
			c = ((v[2] * 4) - 2) * v[2];
			
			if(c < a)
				v[2]++;
			else if(c > a)
				v[0]++;
			else
				break;
		}
	}
}

int main() {
	vector<long long> v = {1, 1, 1};
	
	nextTriangle(v); // Result: {285, 143, 143}
	nextTriangle(v); // Result: {55385, 31977, 27693}
	
	cout << "result = {"
		<< v[0] << ", "
		<< v[1] << ", "
		<< v[2] << "} = "
		<< H(v[2])
		<< endl;
	
	return 0;
}