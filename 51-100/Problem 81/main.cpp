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

int smallestRouteFile(const string &f) {
	int i, x, y;
	Grid g;
	
	g = readFile(f);
	
	for(i = 1; i < (g.size() * 2) - 1; i++) {
		x = (i < g.size()) ? 0 : i - g.size() + 1;
		y = (i < g.size()) ? i : g.size() - 1;
		
		while(y >= 0 && x < g.size()) {
			if(y - 1 < 0)
				g[y][x] += g[y][x - 1];
			else if(x - 1 < 0)
				g[y][x] += g[y - 1][x];
			else 
				g[y][x] += (g[y - 1][x] < g[y][x - 1]) ? g[y - 1][x] : g[y][x - 1];
			
			x++;
			y--;
		}
	}
	
	return g[g.size() - 1][g.size() - 1];
}

int main() {
	cout << "result = " << smallestRouteFile("matrix.txt") << endl;
	
	return 0;
}
