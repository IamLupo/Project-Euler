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
	Find the product abc.
*/

int findProduct(int value) {
	int a, b, c;
	
	for(a = 0; a < value; a++) {
		for(b = a + 1; b < value - a - b - 1; b++) {
			c = value - a - b;
			if(pow(a, 2) + pow(b, 2) == pow(c, 2))
				return a * b * c;
		}
	}
	
	return 0;
}

int main() {
	cout << "result = " << findProduct(1000) << endl;
	
	return 0;
}
