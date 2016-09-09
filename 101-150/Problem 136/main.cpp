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
	How many values of n less than one million have exactly ten distinct solutions?
*/

/*
	n = x^2 - y^2 - z^2
	
	s = start position
	d = distance
	
	n = (s + d)^2 − s^2 − (s − d)^2
	n = 4ds - s^2
	n = s(4d - s)
*/

int f(int l) {
	int d, i, r, s;
	vector<int> v(l, 0);
	
	//Init
	r = 0;
	
	//Calculate total results
	for(s = 0; s < l; s++) 
		for(d = s / 4 + 1; d < s && s * (4 * d - s) < l; d++)
			v[s * (4 * d - s)]++;
	
	//Filter result
	for(i = 1; i < v.size(); i++)
		if(v[i] == 1)
			r++;
	
	return r;
}

int main() {
	cout << "Result = " << f(100) << endl;
	
	return 0;
}
