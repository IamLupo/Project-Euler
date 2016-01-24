#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	What is the value of the first triangle number to have over five hundred divisors?
*/

int firstDivider(int s) {
	int i, j, x;
	vector<int> v;
	
	//Init
	for(i = 0; i <= 77000000; i++)
		v.push_back(1);
	
	//Count dividers
	for(i = 2; i < 33500000; i++) {
		for(j = i; j < 77000000; j += i) {
			v[j]++;
		}
	}
	
	//Search the first s
	x = 1;
	for(i = 1; i < 77000000; i += x) {
		if(v[i] >= s)
			return i;
		x++;
	}
	
	return 0;
}

int main() {
	cout << "result = " << firstDivider(500) << endl;

	return 0;
}