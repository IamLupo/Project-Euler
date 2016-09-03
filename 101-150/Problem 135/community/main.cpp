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
*/

int f(int l) {
	int q, c, r;
	vector<int> count(l,0);
	
	//Init
	r = 0;
	
	//Calculate total results
	for(q = 1; q < l; q++) 
		for(c = q / 4 + 1; c < q && q * (4 * c - q) < l; c++) {
			count[q * (4 * c - q)]++;
			
			//Debug
			//cout << q * (4 * c - q) << " " << q << " " << c << endl;
		}
	
	//Filter
	for(q = 1; q < count.size(); q++)
		if(count[q] == 10)
			r++;
	
	return r;
}

int main() {
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
