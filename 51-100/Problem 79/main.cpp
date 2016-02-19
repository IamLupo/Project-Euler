#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "IamLupo/number.h"
#include "IamLupo/vector.h"

using namespace std;

/*
	Given that the three characters are always asked for in order,
	analyse the file so as to determine the shortest
	possible secret passcode of unknown length.
*/

vector<vector<int>> readFile(const string &f) {
	string v;
	vector<vector<int>> r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			if(v.size() > 1) {
				r.push_back(IamLupo::Vector::to(IamLupo::Number::to(v)));
			}
		}
	}
	
	file.close();
	
	return r;
}

int getPassword(const string &fn) {
	int i, j, k, t;
	vector<int> n, r;
	vector<vector<int>> v, before;
	vector<int>::iterator it;
	bool f;
	
	v = readFile(fn);
	n = {0, 1, 2, 3, 6, 7, 8, 9};
	
	for(i = 0; i < n.size(); i++) { // Loop possible numbers
		r.clear();
		
		for(j = 0; j < v.size(); j++) { //Loop keys
			f = true;
			
			//Watch if number is in key
			it = find(v[j].begin(), v[j].end(), n[i]);
			if(it == v[j].end())
				f = false;
			
			//Loop numbers in key
			for(k = 0; k < v[j].size() && f; k++) {
				//look for numbers that are before the "n[i]" number
				if(v[j][k] == n[i])
					f = false;
				else {
					//Only add them once on the list
					it = find(r.begin(), r.end(), v[j][k]);
					if(it == r.end())
						r.push_back(v[j][k]);
				}
			}
		}
		
		before.push_back(r);
	}
	
	//Generate password
	t = 0;
	for(i = 0; i < n.size(); i++) {
		for(j = 0; j < n.size(); j++) {
			if(i == before[j].size()) {
				t *= 10;
				t += n[j];
			}
		}
	}

	return t;
}

int main() {
	cout << "result = " << getPassword("keylog.txt") << endl;
	
	return 0;
}
