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
	Find the set of four distinct digits, a < b < c < d, for which the longest set of consecutive
	positive integers, 1 to n, can be obtained, giving your answer as a string: abcd.
*/

bool valid(const vector<int> &s, double v, int n) {
	int i, x;
	vector<int> t;
	
	//Check results
	if(s.size() == 0) {
		if(n == v)
			return true;
		else
			return false;
	}
	
	//Loop all values
	for(i = 0; i < s.size(); i++) {
		//Create a new list
		t = s;
		x = t[i];
		t.erase(t.begin()+i);
		
		//When its the first level
		if(v == 0) {
			if(valid(t, x, n))
				return true;
		} else {
			//Check all combinations
			if(	valid(t, v + x, n) || 
				valid(t, v - x, n) || 
				valid(t, v * x, n) || 
				valid(t, v * 1.0 / x, n))
				return true;
			
			/*
				Fix: (a ? b) + (c ? d)
			*/
			if(s.size() == 2) {
				t = s;
				t[0] += t[1];
				t.erase(t.begin()+1);
				if(valid(t, v, n))
					return true;
			}
		}
	}
	
	return false;
}

int findSets(const vector<int> &s) {
	int i;
	vector<int> t;
	bool f;
	
	i = 0;
	f = true;
	
	while(f) {
		f = false;
		t = s;
		
		do {
			if(valid(t, 0, i)) {
				f = true;
				i++;
				break;
			}
		} while(next_permutation(t.begin(), t.end()));
	}
	
	return i;
}

int findHighestDistinctDigits() {
	int i, j, k, l, v, h, r;
	vector<int> s;
	
	h = 0;
	r = 0;
	
	for(i = 1; i < 10; i++) {
		for(j = i + 1; j < 10; j++) {
			for(k = j + 1; k < 10; k++) {
				for(l = i + 1; l < 10; l++) {
					s = {l, k, j, i};
					v = findSets(s);
					
					if(v > h) {
						h = v;
						r = IamLupo::Number::to(s);
					}
				}
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << findHighestDistinctDigits() << endl;
	
	return 0;
}
