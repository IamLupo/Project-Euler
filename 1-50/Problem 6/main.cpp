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
	Find the difference between the sum of the squares of the first one
	hundred natural numbers and the square of the sum.
*/

long long difference(int min, int max) {
	int i, r;
	
	r = 0;
	
	for(i = min; i <= max; i++)
		r += i;
	
	r = pow(r, 2);
	
	for(i = min; i <= max; i++)
		r -= pow(i, 2);
	
	return r;
}

int main() {
	cout << "result = " << difference(1, 100) << endl;
	
	return 0;
}
