#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"

using namespace std;

/*
	Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
	contain the same digits.
*/

int findSmallest(int l) {
	int i, j, c;
	vector<int> v, t;
	bool f;
	
	c = pow(10, l) / 6;
	
	for(i = pow(10, l - 1); i < c; i++) {
		v = IamLupo::Vector::to(i);
		f = true;
		
		sort(v.begin(), v.end());
		
		for(j = 2; j <= l && f; j++) {
			t = IamLupo::Vector::to(j * i);
			sort(t.begin(), t.end());
			
			if(!IamLupo::Vector::same(v, t))
				f = false;
		}
		
		if(f)
			return i;
	}
	
	return -1;
}

int main() {
	cout << "result = " << findSmallest(6) << endl;
	
	return 0;
}