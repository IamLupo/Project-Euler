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
	If dn represents the nth digit of the fractional part,
	find the value of the following expression.
	
	d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
*/

int find(long long p) {
	long long l, t, r, v;
	
	l = 1;		// Total digits
	t = 10;		// Max range till digits increases
	
	while(p >= t) {
		p -= t;							// Subtract the max until we find the remaining
		l++;							// Increase total digits
		t = l * 9 * pow(10, l - 1);		// Calculate max of next range
	}
	
	//Calculate the number p is pointing
	v = pow(10, l - 1) + (p / l);
	
	//Calculate the position of v
	r = (long long)pow(10, l - 1 - (p % l));

	return (v / r) % 10;
}

int productOfFractionals(int l) {
	int i, r;
	
	//Init
	r = 1;
	
	for(i = 10; i <= l; i *= 10)
		r *= find(i);
	
	return r;
}

int main() {
	cout << "result = " << productOfFractionals(1000000) << endl;
	
	return 0;
}