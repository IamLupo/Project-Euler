#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	What is the largest n-digit pandigital prime that exists?
*/

vector<int> readFile(const string &f) {
	int i, v;
	string s;
	vector<int> r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, s, ',');
			
			//Convert
			v = 0;
			for(i = 0; i < s.size(); i++)
				if(s[i] != '"')
					v += (int)s[i] - 64;
			
			//Save result
			r.push_back(v);
		}
	}
	
	file.close();
	
	return r;
}

bool isTriangle(int v) {
	int t, x;
	
	x = 1;
	t = 1;
	
	while(t < v) {
		x += 1;
		t += x;
	}
	
	if(t == v)
		return true;
	
	return false;
}

int countTriangleWords(const string &f) {
	int i, r;
	vector<int> v;
	
	//Init
	r = 0;
	v = readFile(f);
	
	for(i = 0; i < v.size(); i++)
		if(isTriangle(v[i]))
			r++;
	
	return r;
}

int main() {
	cout << "result = " << countTriangleWords("words.txt") << endl;
	
	return 0;
}