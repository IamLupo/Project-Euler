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
	int i, j, x, y;
	Grid g, c;
	
	//Init
	g = readFile(f);
	c = g;
	
	//Calc values by only move to right and down
	for(i = 1; i < (g.size() * 2) - 1; i++) {
		x = (i < g.size()) ? 0 : i - g.size() + 1;
		y = (i < g.size()) ? i : g.size() - 1;
		
		while(y >= 0 && x < g.size()) {
			if(y - 1 < 0)
				c[y][x] += c[y][x - 1];
			else if(x - 1 < 0)
				c[y][x] += c[y - 1][x];
			else 
				c[y][x] += (c[y - 1][x] < c[y][x - 1]) ? c[y - 1][x] : c[y][x - 1];
			
			x++;
			y--;
		}
	}
	
	//Update now all values by moving all directions
	for(i = 0; i < c.size(); i++) {
		for(j = 0; j < c[i].size(); j++) {
			//Check Up
			if(i - 1 >= 0) {
				if(c[i - 1][j] > c[i][j] + g[i - 1][j]) {
					c[i - 1][j] = c[i][j] + g[i - 1][j];
					
					i--;
					j--;
				}
			}
			
			//Check Down
			if(i + 1 < c.size()) {
				if(c[i + 1][j] > c[i][j] + g[i + 1][j]) {
					c[i + 1][j] = c[i][j] + g[i + 1][j];
				}
			}
			
			//Check Left
			if(j - 1 >= 0) {
				if(c[i][j - 1] > c[i][j] + g[i][j - 1]) {
					c[i][j - 1] = c[i][j] + g[i][j - 1];
					
					i = 0;
					j = 0;
				}
			}
			
			//Check Right
			if(j + 1 < c.size()) {
				if(c[i][j + 1] > c[i][j] + g[i][j + 1]) {
					c[i][j + 1] = c[i][j] + g[i][j + 1];
				}
			}
		}
	}
	
	return c[c.size() - 1][c.size() - 1];
}

int main() {
	cout << "result = " << smallestRouteFile("matrix.txt") << endl;
	
	return 0;
}
