#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "IamLupo/string.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the minimal path sum of the 80 by 80 matrix,
	from the top left to the bottom right by only moving right and down.
*/

typedef vector<vector<int>> Grid;
typedef vector<int> Level;

Grid readFile(const string &f) {
	int i;
	string v;
	vector<string> t;
	vector<int> c;
	Grid r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			if(v.size() > 1) {
				c.clear();
				t = IamLupo::String::explode(v, ',');
				
				for(i = 0; i < t.size(); i++) {
					c.push_back(IamLupo::Number::to(t[i]));
				}
				r.push_back(c);
			}
		}
	}
	
	file.close();
	
	return r;
}

Level nextLevel1(const Grid &v, const Level &l) {
	int i, j, x, y;
	Level r;
	
	x = 0;
	y = l.size();
	
	for(i = 0; i <= l.size(); i++) {
		if(i == 0)
			r.push_back(v[y][x] + l[i]);
		else if(i == l.size())
			r.push_back(v[y][x] + l[i - 1]);
		else
			r.push_back((l[i] < l[i - 1]) ? v[y][x] + l[i] : v[y][x] + l[i - 1]);
		
		x++;
		y--;
	}
	
	return r;
}

Level nextLevel2(const Grid &v, const Level &l) {
	int i, x, y;
	Level r;
	
	x = v.size() - l.size() + 1;
	y = v.size() - 1;
	
	for(i = 0; i < l.size() - 1; i++) {
		r.push_back((l[i] < l[i + 1]) ? v[y][x] + l[i] : v[y][x] + l[i + 1]);

		x++;
		y--;
	}
	
	return r;
}

int smallestRouteFile(const string &f) {
	int i, j, r;
	Grid v;
	Level l;
	
	v = readFile(f);
	l = {v[0][0]};
	
	for(i = 0; i < v.size() - 1; i++)
		l = nextLevel1(v, l);
	
	for(i = 0; i < v.size() - 1; i++)
		l = nextLevel2(v, l);
	
	sort(l.begin(), l.end());
	
	return l[0];
}

int main() {
	cout << "result = " << smallestRouteFile("matrix.txt") << endl;
	
	return 0;
}
