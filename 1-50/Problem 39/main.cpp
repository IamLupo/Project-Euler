#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

using namespace std;

/*
	For which value of p ≤ 1000, is the number of solutions maximised?
*/

/*
	https://en.wikipedia.org/wiki/Special_right_triangle#Common_Pythagorean_triples
	
    m^2 − n^2 : 2mn : m^2 + n^2
*/
int getMaxAnglesTriangle(int max) {
	int i, a, b, c, m, n, t, r;
	vector<set<int>> v;
	bool f;
	
	//Init
	f = true;
	t = 0;
	r = 0;
	
	//Make empty list
	for(i = 0; i < max + 1; i++)
		v.push_back({});
	
	for(m = 2; 2 * m * m < max; m++) {
		for(n = 1; m > n; n++) {
			a = (m * m) - (n * n);
			b = 2 * m * n;
			c = (m * m) + (n * n);
			
			t = a + b + c;
			
			i = 1;
			while(t * i <= max) {
				v[t * i].insert(a * i);
				v[t * i].insert(b * i);
				v[t * i].insert(c * i);
				
				i++;
			}
		}
	}
	
	//Find the most solutions
	t = 0;
	for(i = 1; i < v.size(); i++) {
		if(t < v[i].size()) {
			t = v[i].size();
			r = i;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << getMaxAnglesTriangle(1000) << endl;
	
	return 0;
}