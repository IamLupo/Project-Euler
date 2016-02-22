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

Level NextLevel(const Grid &v, const Level &l, int index) {
	int i;
	Level r;
	
	//Generate result from left to right
	for(i = 0; i < l.size(); i++)
		r.push_back(v[i][index] + l[i]);
	
	//Find potential up or down that generate lower values
	for(i = 0; i < r.size(); i++) {
		if(i != 0 && r[i - 1] > r[i] + v[i - 1][index]) {
			r[i - 1] = r[i] + v[i - 1][index];
			i = 0;
		}
		
		if(i + 1 != r.size() && r[i + 1] > r[i] + v[i + 1][index]) {
			r[i + 1] = r[i] + v[i + 1][index];
			i = 0;
		}
	}
	
	return r;
}

int smallestRouteFile(const string &f) {
	int i, r;
	Grid v;
	Level l;
	
	//Init
	v = readFile(f);
	
	//Copy left side numbers
	for(i = 0; i < v.size(); i++)
		l.push_back(v[i][0]);
	
	//Calc smallest to right
	for(i = 1; i < v.size(); i++)
		l = NextLevel(v, l, i);
	
	//get smallest at first position
	sort(l.begin(), l.end());
	
	return l[0];
}

int main() {
	cout << "result = " << smallestRouteFile("matrix.txt") << endl;
	
	return 0;
}
