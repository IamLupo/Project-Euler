#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many different ways can one hundred be written as
	a sum of at least two positive integers?
*/

int countWays(int n) {
	int i, j;
	vector<long long> a(n + 1, 0);
	
	//Init
	a[0] = 1;
	
	//Calc
	for(i = 1; i < n; i++) {
		for(j = i; j <= n; j++) {
			a[j] += a[j - i];
		}
	}
	
	return a[n];
}

int main() {
	cout << "result = " << countWays(100) << endl;

	return 0;
}