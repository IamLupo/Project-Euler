#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "IamLupo/triangular.h"

using namespace std;

/*
	Find the least value of M such that the number of solutions first exceeds one million.
*/

int findM(int l) {
	int m, y, z, t, v, r;
	
	r = 0;
	m = 1;
	
	while(1) {
		for(y = 1; y <= m; y++) {
			for(z = 1; z <= y; z++) {
				v = pow(m, 2) + pow((y + z), 2);
				t = sqrt(v);
				
				if(t * t == v) {
					r++;
					
					if(r >= l)
						return m;
				}
			}
		}
		
		m++;
	}
	
	return -1;
}

int main() {
	cout << "result = " << findM(1000000) << endl;
	
	return 0;
}
