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
	By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner
	of each solution grid; for example, 483 is the 3-digit number found in the top left corner of
	the solution grid above.
*/

typedef vector<vector<int>> Sudoku;

bool valid(const Sudoku &s, int y, int x) {
	int i, j, v, c, gx, gy;
	
	v = s[y][x];
	
	//Horizontal
	for(i = 0; i < 9; i++)
		if(i != x && v == s[y][i])
			return false;
	
	//Vertical
	for(i = 0; i < 9; i++)
		if(i != y && v == s[i][x])
			return false;
	
	//Group
	gx = x / 3 * 3;
	gy = y / 3 * 3;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			if(gx + i != x && gy + j != y && v == s[gy + j][gx + i])
				return false;
	
	return true;
}

bool solve(Sudoku &s, int id) {
	int i, x, y;
	
	//if reached end
	if(id == 81)
		return true;
	
	//Calculate position
	x = id % 9;
	y = id / 9;
	
	//already filled position
	if(s[y][x] != 0)
		return solve(s, id + 1);
	
	//bruteforce all answers
	for(i = 1; i <= 9; i++) {
		s[y][x] = i;
		
		if(valid(s, y, x) && solve(s, id + 1))
			return true;
	}
	
	//no possible values found return to default value
	s[y][x] = 0;
	
	return false;
}

void init(Sudoku &s) {
	int i;
	
	s.clear();
	
	for(i = 0; i < 9; i++)
		s.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
}

vector<Sudoku> readFile(const string &f) {
	int i, j, n;
	string v;
	Sudoku s;
	vector<Sudoku> r;
	ifstream file(f);
	
	//Initialize sudoku
	init(s);
	
	if(file.is_open()) {
		while(file.good()) {
			//First line is trash
			getline(file, v);
			
			//read sudoku data
			for(i = 0; i < 9; i++) {
				//read data
				getline(file, v);
				
				for(j = 0; j < 9; j++)
					//Convert to integer
					s[i][j] = IamLupo::Number::to(v.substr(j, 1));
			}
			
			//save sudoku
			r.push_back(s);
		}
	}
	
	file.close();
	
	return r;
}

int sumSudoku(const string &f) {
	int i, r;
	vector<Sudoku> s;
	
	r = 0;
	s = readFile(f);
	
	for(i = 0; i < s.size(); i++) {
		solve(s[i], 0);
		
		r += s[i][0][0] * 100;
		r += s[i][0][1] * 10;
		r += s[i][0][2];
	}
	
	return r;
}

int main() {
	cout << "result = " << sumSudoku("sudoku.txt") << endl;
	
	return 0;
}
