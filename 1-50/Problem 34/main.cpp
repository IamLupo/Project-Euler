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
	Find the sum of all numbers which are equal to the sum of the factorial of their digits.
*/

int sumCurious() {
	int i, j, v, r;
	vector<int> o;

	//Init
	r = 0;
	o = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	
	for(i = 10; i < 41000; i++) {
		v = 0;
		
		for(j = i; j > 0; j /= 10)
			v += o[j % 10];
		
		if(v == i)
			r += v;
	}
	
	return r;
}

int main() {
	cout << "result = " << sumCurious() << endl;
	
	return 0;
}