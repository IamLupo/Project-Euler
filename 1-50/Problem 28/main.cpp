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
	What is the sum of the numbers on the diagonals in a 1001 by 1001
	spiral formed in the same way?
*/

int sumDiagonals(int x, int y) {
	int a, b, s, r;
	
	s = x * y;
	a = 1;
	b = 2;
	r += a;
	
	while(a < s) {
		r += (a * 4) + (b * 10);
		a += (b * 4);		
		b += 2;
	}
	
	return r;
}

int main() {
	cout << "result = " << sumDiagonals(1001, 1001) << endl;
	
	return 0;
}