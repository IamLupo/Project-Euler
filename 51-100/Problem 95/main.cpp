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
	Find the smallest member of the longest amicable chain with no element
	exceeding one million.
*/

vector<int> readFile(const string &f) {
	string v;
	vector<int> r;
	ifstream file(f);
	
	r.push_back(0);
	
	if(file.is_open()) {
		while(file.good()) {
			//Read line
			getline(file, v);
			
			//Convert and Save
			r.push_back(IamLupo::Number::to(v));
		}
	}
	
	file.close();
	
	return r;
}

vector<int> chain(const vector<int> &d, int n) {
	int v;
	vector<int> l, r;
	vector<int>::iterator it;
	
	v = n;
	it = l.begin();
	
	while(it == l.end()) {
		//save value
		l.push_back(v);
		
		//get next value
		v = d[v];
		
		//value exceeded 1 milion
		if(v >= 1000000)
			return {0};
		
		//Look if we found a closing loop
		it = find(l.begin(), l.end(), v);
	}
	
	sort(l.begin(), l.end());
	
	//when start potion is also ending point
	if(v == n) {
		r.push_back(l.size());
		r.push_back(l[0]);
		
		return r;
	}
	
	return {0};
}

int findAmicableChain(const string &f) {
	int i, h, r;
	vector<int> d, t;
	
	//Init
	h = 0;
	r = 0;
	d = readFile(f);
	
	for(i = 1; i < d.size(); i++) {
		t = chain(d, i);
		
		if(h < t[0]) {
			h = t[0];
			r = t[1];
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << findAmicableChain("data.txt") << endl;
	
	return 0;
}
