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
	How many starting numbers below ten million will arrive at 89?
*/

static vector<int> list(10000000, 0);

bool chain(int n) {
	int v, d, n2;
	
	if(list[n] == 1)
		return true;
	
	//Init
	v = n;
	n2 = 0;
	
	//Generate next value
	while(v) {
		d = v % 10;
		n2 += d * d;
		v /= 10;
	}
	
	//Check if next value already been checked
	if(list[n2] != 0) {
		list[n] = list[n2];
		return (list[n2] == 1);
	} else {
		// If next value dont exist yet, generate next level
		if(chain(n2)) {
			list[n] = 1;
			return true;
		} else {
			list[n] = -1;
			return false;
		}
	}
}

int f(int l) {
	int i, r;
	
	//Init
	r = 0;
	list[1]--;
	list[89]++;

	for (i = 1; i < l; i++)
		r += chain(i);

	return r;
}

int main() {
	cout << "Result = " << f(10000000) << endl;
	
	return 0;
}
