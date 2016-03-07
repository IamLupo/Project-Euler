#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/string.h"
#include "IamLupo/number.h"

using namespace std;

/*
	What is the greatest product of four adjacent numbers in the same
	direction (up, down, left, right, or diagonally) in the 20×20 grid?
*/

typedef vector<vector<int>> Grid;

Grid readFile(const string &f) {
	int i;
	string v;
	vector<string> t;
	vector<int> l;
	Grid r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			t = IamLupo::String::explode(v, ' ');
			
			l.clear();
			
			for(i = 0; i < t.size(); i++)
				l.push_back(IamLupo::Number::to(t[i]));
			
			r.push_back(l);
		}
	}
	
	file.close();
	
	return r;
}

long long highestDiagonal(const Grid &g, int x, int y, int d, int dir) {
	int i, j, p, r;
	
	//Init
	r = 0;
	d -= 1;
	
	while(x + (d * dir) < g.size() && x + (d * dir) >= 0 && y + d < g.size()) {
		p = 1;
		for(j = 0; j <= d; j++)
			p *= g[y + j][x + (j * dir)];
		
		if(p > r)
			r = p;
		
		x += dir;
		y++;
	}
	
	return r;
}

long long  greatestProduct(const string &f, int d) {
	int i;
	vector<int> r;
	Grid g;
	
	g = readFile(f);
	
	for(i = 0; i < g.size(); i++) {
		r.push_back(highestDiagonal(g, i, 0, d, 1));
		r.push_back(highestDiagonal(g, i, 0, d, -1));
		r.push_back(highestDiagonal(g, 0, i, d, 1));
		r.push_back(highestDiagonal(g, g.size() - 1, i, d, -1));
	}
	
	sort(r.begin(), r.end());
	
	return r[r.size() - 1];
}

int main() {
	cout << "result = " << greatestProduct("data.txt", 4) << endl;
	
	return 0;
}
