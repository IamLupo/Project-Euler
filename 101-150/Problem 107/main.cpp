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
	Find the maximum saving which can be achieved by removing redundant edges
	whilst ensuring that the network remains connected.
*/

typedef vector<vector<int>> Matrix;

Matrix readFile(const string &f) {
	int i;
	string v;
	vector<string> l;
	Matrix r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			vector<int> t;
			
			getline(file, v);
			l = IamLupo::String::explode(v, ',');
			
			for(i = 0; i < l.size(); i++) {
				if(l[i].compare("-") != 0)
					t.push_back(IamLupo::Number::to(l[i]));
				else
					t.push_back(0);
			}
			
			r.push_back(t);
		}
	}
	
	file.close();
	
	return r;
}

int total_weight(const Matrix &m) {
	int r, i, j;
	
	r = 0;
	
	for(i = 0; i < m.size(); i++)
		for(j = 0; j < i + 1; j++)
			r += m[i][j];
	
	return r;
}

int update(const Matrix &m, vector<int> &conn, vector<int> &disconn) {
	int i, j, v, p, r;
	
	//Init
	r = -1;
	
	for(i = 0; i < conn.size(); i++) {
		for(j = 0; j < disconn.size(); j++) {
			v = m[conn[i]][disconn[j]];
			
			if(v != 0) {
				if(r == -1 || v < r) {
					r = v;
					p = disconn[j];
				}
			}
		}
	}
	
	//Update connected and disconnected list
	conn.push_back(p);
	disconn.erase(remove(disconn.begin(), disconn.end(), p), disconn.end());
	
	return r;
}

int smallest(const Matrix &m) {
	int i, r;
	vector<int> conn, disconn;
	
	//Init
	r = 0;
	conn = {0};
	for(i = 1; i < m.size(); i++)
		disconn.push_back(i);
	
	//Find connections
	for(i = 1; i < m.size(); i++)
		r += update(m, conn, disconn);
	
	return r;
}

int saving(const string &f) {
	int i;
	Matrix m;
	
	//Init
	m = readFile(f);
	
	return total_weight(m) - smallest(m);
}

int main() {
	//cout << "Result = " << saving("example.txt") << endl;
	cout << "Result = " << saving("network.txt") << endl;
	
	return 0;
}
