#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/number.h"
#include "IamLupo/string.h"

using namespace std;

/*
	Find the maximum total from top to bottom of the triangle.
*/

typedef vector<int> Level;
typedef vector<Level> Triangle;

Triangle readFile(const string &f) {
	int i;
	string v;
	vector<string> r;
	Level l;
	Triangle t;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			if(v.size() > 1) {
				l.clear();
				r = IamLupo::String::explode(v, ' ');
				
				for(i = 0; i < r.size(); i++) {
					//Save
					l.push_back(IamLupo::Number::to(r[i]));
				}
				
				t.push_back(l);
			}
		}
	}
	
	file.close();
	
	return t;
}

Level next(const Level a, const Level b) {
	int i, x, y;
	Level r;
	
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
	Level l_next;
	Triangle t;
	
	t = readFile(f);
	s = t.size();
	
	l_next = t[s - 1];
	
	for(i = 0; i < s - 1; i++)
		l_next = next(t[s - 2 - i], l_next);
	
	return l_next[0];
}

int main() {
	cout << "result = " << getHighestSum("triangle.txt") << endl;
	
	return 0;
}