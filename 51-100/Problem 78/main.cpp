#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	Find the least value of n for which p(n) is divisible by one million.
*/

int getN(int l) {
	int i, j;
	vector<int> a(100001, 0);
	
	//Init
	i = 0;
	a[0] = 1;
	
	//Calc
	for(i = 1; i <= 100000; i++) {
		for(j = i; j <= 100000; j++) {
			a[j] += a[j - i];
			a[j] %= l;
		}
		
		if(a[i] == 0)
			return i;
	}
	
	return -1;
}

int main() {
	cout << getN(1000000) << endl;
	
	return 0;
}
