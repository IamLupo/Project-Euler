#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/number.h"

using namespace std;

/*
	Find the sum of the only ordered set of six cyclic 4-digit numbers for
	which each polygonal type: triangle, square, pentagonal, hexagonal,
	heptagonal, and octagonal, is represented by a different number in the set.
*/

/*
	Triangle 	  	f(0, n) = n(n+1)/2
	Square 	  		f(1, n) = n2
	Pentagonal 	  	f(2, n) = n(3n−1)/2
	Hexagonal 	  	f(3, n) = n(2n−1)
	Heptagonal 	  	f(4, n) = n(5n−3)/2
	Octagonal 	  	f(5, n) = n(3n−2)
*/
int p(int i, int v) {
	switch(i) {
		case 0:
			return ((v * v) + v) / 2;
		break;
		case 1:
			return v * v;
		break;
		case 2:
			return ((3 * v * v) - v) / 2;
		break;
		case 3:
			return (2 * v * v) - v;
		break;
		case 4:
			return ((5 * v * v) - (3 * v)) / 2;
		break;
		case 5:
			return (3 * v * v) - (2 * v);
		break;
	}
	
	cout << "oeps!" << endl;
	return -1;
}

void bruteforce(vector<int> &x, vector<int> &y, int* h, int n, int l, int m) {
	int i, j, v;
	vector<int> x2, y2;
	
	// level is max
	if(l == m) {
		/*
			if first number with first part is same as last number with last part
			
			Example:
				f(9918, 1815) = true, because 18
				f(5678, 7700) = false, because 78 != 77
		*/
		if(x[0] % 100 == x[m - 1] / 100)
			*h = IamLupo::Number::sum(x);
		
		return;
	}
	
	//Loop all polygonal types
	for(j = 0; j < m; j++) {
		//Check if polygonal types is used before
		if(find(y.begin(), y.end(), j) == y.end()) {
			//Save polygonal type
			y2 = y;
			y2.push_back(j);
			
			//Loop all possible values in polygonal type
			for(i = 0, v = 0; v < 10000; i++) {
				v = p(j, i);
				
				if(v % 100 == n || l == 0) {
					//Check if index is in range or if is used before
					if(v >= 1000 && v < 10000 && find(x.begin(), x.end(), v) == x.end()) {
						//Save polygonal value
						x2 = x;
						x2.push_back(v);
						
						bruteforce(x2, y2, h, v / 100, l + 1, m);
					}
				}
			}
		}
	}
}

int sumOrderedCyclicNumbers(int m) {
	int h;
	vector<int> x, y;
	
	//Init
	h = 0;
	
	//Rock and roll! :D
	bruteforce(x, y, &h, 100, 0, m);
	
	return h;
}

int main() {
	cout << "result = " << sumOrderedCyclicNumbers(6) << endl;
	
	return 0;
}