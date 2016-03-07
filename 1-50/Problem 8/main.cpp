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
	Find the thirteen adjacent digits in the 1000-digit number that have the greatest product.
	What is the value of this product?
*/

vector<int> readFile(const string &f) {
	int i;
	string v;
	vector<int> r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			for(i = 0; i < v.size(); i++)
				r.push_back(IamLupo::Number::to(v.substr(i, 1)));
		}
	}
	
	file.close();
	
	return r;
}

long long  greatestProduct(const string &f, int d) {
	int i, j;
	long long t, r;
	vector<int> v;
	
	r = 0;
	v = readFile(f);
	
	for(i = 0; i < v.size() - d; i++) {
		t = 1;
		
		for(j = 0; j < d; j++)
			t *= v[i + j];
		
		if(t > r)
			r = t;
	}
	
	return r;
}

int main() {
	cout << "result = " << greatestProduct("data.txt", 13) << endl;
	
	return 0;
}
