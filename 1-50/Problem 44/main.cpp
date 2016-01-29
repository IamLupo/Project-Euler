#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference
	are pentagonal and D = |Pk − Pj| is minimised; what is the value of D?
*/

bool isPentagonal(int v) {
	int i, x, t;
	
	t = 1;
	x = 1;
	
	while(t < v) {
		x += 3;
		t += x;
	}
	
	if(v == t)	
		return true;
	
	return false;
}

int f(int x) {
	return ((3 * x * x) - x) / 2; 
}

int getDifferencePentagonal() {
	int k, j, d;
	
	for(k = 1; k < 10000; k++) {
		for(j = 1; j < k; j++) {
			if(isPentagonal(f(k) + f(j))) {
				d = f(k) - f(j);
				d = (d >= 0) ? d : d * -1;
				
				if(isPentagonal(d)) {
					return d;
				}
			}
		}
	}
	
	return 0;
}

int main() {
	cout << "result = " << getDifferencePentagonal() << endl;
	
	return 0;
}