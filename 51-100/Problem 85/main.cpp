#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
	Although there exists no rectangular grid that contains exactly two million rectangles,
	find the area of the grid with the nearest solution.
*/

/*
	grid(1, 1) = 1
	grid(2, 1) = 2 + 1 = 3
	grid(3, 1) = 3 + 2 + 1 = 6
	grid(4, 1) = 4 + 3 + 2 + 1 = 10
	grid(5, 1) = 5 + 4 + 3 + 2 + 1 = 15
	
	grid(2, 2) = grid(2, 1) * grid(2, 1) = 9
	grid(3, 2) = grid(3, 1) * grid(2, 1) = 18
	grid(4, 2) = grid(4, 1) * grid(2, 1) = 30
	grid(5, 2) = grid(5, 1) * grid(2, 1) = 45
	
	grid(2, 3) = grid(2, 1) * grid(3, 1) = 18
	....
*/

vector<int> generate(int l) {
	int x, y;
	vector<int> r;
	
	//Init
	x = 1;
	y = 1;
	
	while(x <= l) {
		r.push_back(x);
		y++;
		x += y;
	}
	
	return r;
}

int getNearestArea(int a) {
	int i, j, r, h, d, t;
	vector<int> v;
	
	//Init
	r = 0;
	h = -1;
	v = generate(3500);
	
	for(i = 0; i < v.size(); i++) {
		for(j = 0; j < v.size(); j++) {
			//calc possibilities
			t = v[i] * v[j];
			
			//calc distance to objective
			d = (a >= t) ? a - t : t - a;
			
			//found a smaller distance to our answer
			if(h == -1 || h > d) {
				h = d;
				
				//Calc area
				r = (i + 1) * (j + 1);
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << getNearestArea(2000000) << endl;
	
	return 0;
}
