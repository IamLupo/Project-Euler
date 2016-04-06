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
	Which starting number, under one million, produces the longest chain?
*/

int getLongestChain(int m) {
	int i, c, h, r;
	long long value;
	
	//Init
	h = 0;
	r = 0;
	
	for(i = (((m / 2) % 2) == 1) ? m / 2 : m / 2 + 1; i <= m; i += 2) {
		value = i;
		c = 0;
		
		while(value != 1) {
			if(value % 2 == 0)
				value /= 2;
			else
				value = (value * 3) + 1;
			c++;
		}
		
		if(h < c) {
			h = c;
			r = i;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << getLongestChain(1000000) << endl;
	
	return 0;
}
