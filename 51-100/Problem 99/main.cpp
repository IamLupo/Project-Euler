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
	determine which line number has the greatest numerical value
*/

typedef vector<int> Pair;

vector<Pair> readFile(const string &f) {
	string v;
	vector<string> t;
	Pair p;
	vector<Pair> r;
	ifstream file(f);
	
	//Init
	p = {0, 0};
	
	if(file.is_open()) {
		while(file.good()) {
			//First line is trash
			getline(file, v);
			
			//Separate base and exponent
			t = IamLupo::String::explode(v, ',');
			
			//Convert to integer
			p[0] = IamLupo::Number::to(t[0]);
			p[1] = IamLupo::Number::to(t[1]);
			
			//save Pair
			r.push_back(p);
		}
	}
	
	file.close();
	
	return r;
}

int findHighestValue(const string &f) {
	int i, h, v, r;
	vector<Pair> p;
	
	//Init
	r = 0;
	h = 0;
	p = readFile(f);
	
	for(i = 0; i < p.size(); i++) {
		v = log(p[i][0]) * p[i][1];
		
		if(h < v) {
			r = i;
			h = v;
		}
	}
	
	return r + 1;
}

int main() {
	cout << "result = " << findHighestValue("base_exp.txt") << endl;
	
	return 0;
}
