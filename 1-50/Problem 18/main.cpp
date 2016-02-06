#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

using namespace std;

/*
	Find the maximum total from top to bottom of the triangle.
*/

typedef vector<int> TriangleLevel;
typedef vector<TriangleLevel> Triangle;

const vector<string> explode(const string &s, const char &c) {
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

Triangle readFile(const string &f) {
	int i, n;
	string::size_type sz;
	string line;
	vector<string> r;
	TriangleLevel trl;
	Triangle tr;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, line);
			
			if(line.size() > 1) {
				trl.clear();
				r = explode(line, ' ');
				
				for(i = 0; i < r.size(); i++) {
					//Convert
					n = stoi(r[i], &sz);
					
					//Save
					trl.push_back(n);
				}
				
				tr.push_back(trl);
			}
		}
	}
	
	file.close();
	
	return tr;
}

TriangleLevel next(const TriangleLevel a, const TriangleLevel b) {
	int i, x, y;
	TriangleLevel r;
	
	for(i = 0; i < a.size(); i++) {
		x = a[i] + b[i];
		y = a[i] + b[i + 1];
		
		if(x > y)
			r.push_back(x);
		else
			r.push_back(y);
	}
	
	return r;
}

int getHighestSum(const string &f) {
	int i, j, s;
	TriangleLevel trl_next;
	Triangle tr;
	
	tr = readFile(f);
	s = tr.size();
	
	trl_next = tr[s - 1];
	
	for(i = 0; i < s - 1; i++) {
		trl_next = next(tr[s - 2 - i], trl_next);
	}
	
	return trl_next[0];
}

int main() {
	cout << "result = " << getHighestSum("triangle.txt") << endl;
	
	return 0;
}