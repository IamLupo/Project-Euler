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
	For m = 50, find the least value of n for which the fill-count function first exceeds one million.
*/

static int MINIMUM = 50;

long long count(int v, int len) {
	int i, j;
	long long r;
	
	//Init
	r = 1;
	
	for(i = 1; v + i <= len; i++)
		r++;
	
	for(i = 1; i <= len - v; i++)
		for(j = MINIMUM; j <= len - v - i; j++)
			r += count(j, len - v - i);
	
	return r;
}

long long f(int l) {
	int i, j;
	long long r;
	
	//Init
	for(i = MINIMUM; i <= 1000; i++) {
		r = 1;
		
		for(j = MINIMUM; j <= i; j++)
			r += count(j, i);
		
		//cout << r << endl;
		
		if(r > l)
			return i;
	}
	
	return -1; // Unknown
}

int main() {
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
