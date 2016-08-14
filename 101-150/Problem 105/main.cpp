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
	Identify all the special sum sets, A1, A2, ..., Ak,
	and find the value of S(A1) + S(A2) + ... + S(Ak).
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
			
			for(i = 0; i < l.size(); i++)
				t.push_back(IamLupo::Number::to(l[i]));
			
			r.push_back(t);
		}
	}
	
	file.close();
	
	return r;
}

/*
	Rule I: S(B) ≠ S(C); that is, sums of subsets cannot be equal.
*/
bool validate1(const vector<int> &v, vector<int> &l, int n, int p) {
	int i, x;
	
	for(i = p; i < v.size(); i++) {
		x = n + v[i];
		
		//Check subset is in the list
		if(find(l.begin(), l.end(), x) != l.end())
			return false;
		
		//Add subset to the list
		l.push_back(x);
		
		//Validate next level
		if(!validate1(v, l, x, i + 1))
			return false;
	}
	
	return true;
}

/*
	Rule II: If B contains more elements than C then S(B) > S(C).
*/
bool validate2(const vector<int> &v) {
	int i, x, y;
	
	//Init
	x = v[0]; // x has one element more, this means x must always be the biggest
	y = 0;
	
	for(i = 1; i <= v.size() / 2; i++) {
		x += v[i]; // Add the smallest value
		y += v[v.size() - i]; // Add the highest value
		
		if(x <= y)
			return false;
	}
	
	return true;
}

int f(const string &f) {
	int i, r;
	Matrix m;
	vector<int> v, l;
	
	//Init
	r = 0;
	m = readFile(f);
	
	for(i = 0; i < m.size(); i++) {
		//Init
		v = m[i];
		l.clear(); // Make subset list empty
		
		//Sort values
		sort(v.begin(), v.end());
		
		if(validate2(v) && validate1(v, l, 0, 0))
			r += accumulate(v.begin(), v.end(), 0);
	}
	
	return r;
}

int main() {
	cout << "Result = " << f("sets.txt") << endl;
	
	return 0;
}
