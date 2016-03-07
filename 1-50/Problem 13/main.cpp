#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

using namespace std;

/*
	Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
*/

vector<string> readFile(const string &f) {
	int i;
	string v;
	vector<string> r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			r.push_back(v);
		}
	}
	
	file.close();
	
	return r;
}

string sum(const string &f) {
	int i;
	string r;
	vector<string> v;
	mpz_t a, b;
	
	//Init
	v = readFile(f);
	mpz_init_set_ui(a, 0);
	mpz_init(b);
	
	for(i = 0; i < v.size(); i++) {
		mpz_set_str(b, v[i].c_str(), 10);
		mpz_add(a, a, b);
	}
	
	r = mpz_get_str(nullptr, 10, a);
	
	return r.substr(0, 10);
}

int main() {
	cout << "result = " << sum("input.txt") << endl;
	
	return 0;
}
