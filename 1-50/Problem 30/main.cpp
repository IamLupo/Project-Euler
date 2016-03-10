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
	Find the sum of all the numbers that can be written as the sum
	of fifth powers of their digits.
*/

static vector<int> options;

int bruteforce(int v, int s, int l, int m) {
	int i, r;
	
	r = 0;
	
	if(l == m) {
		if(v == s && v != 1)
			return v;
		
		return 0;
	}
	
	for(i = 0; i < options.size(); i++)
		r += bruteforce(
			v + options[i],
			s + (i * pow(10, l)),
			l + 1,
			m
		);
		
	return r;
}

int sumNumbersOfPowers(int d) {
	int i;
	
	//Calculate powers
	for(i = 0; i < 10; i++)
		options.push_back(pow(i, d));
	
	//Find numbers
	return bruteforce(0, 0, 0, d + 1);
}

int main() {
	cout << "result = " << sumNumbersOfPowers(5) << endl;
	
	return 0;
}