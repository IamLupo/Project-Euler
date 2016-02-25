#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/roman.h"

using namespace std;

/*
	Find the number of characters saved by writing each of these in their minimal form.
*/

vector<string> readFile(const string &f) {
	int i;
	string l;
	vector<string> r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, l);
			r.push_back(l);
		}
	}
	
	file.close();
	
	return r;
}

int countMinimalRomanCharters(const string &f) {
	int i, r, n;
	string s;
	vector<string> v;
	
	r = 0;
	v = readFile(f);
	
	for(i = 0; i < v.size(); i++) {
		s = IamLupo::Roman::to(IamLupo::Roman::to(v[i]));
		r += v[i].size() - s.size();
	}
	
	return r;
}

int main() {
	cout << "result = " << countMinimalRomanCharters("roman.txt") << endl;
	
	return 0;
}
