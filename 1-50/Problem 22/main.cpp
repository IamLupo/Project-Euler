#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

/*
	What is the total of all the name scores in the file?
*/

using namespace std;

vector<string> readFile(const string &f) {
	string temp;
	vector<string> r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, temp, '"');
			
			if(temp.size() > 1) {
				r.push_back(temp);
			}
		}
	}
	
	file.close();
	
	return r;
}

long long calcScore(const string &f) {
	int i, j;
	long long r;
	vector<string> v;
	
	//Init
	r = 0;
	v = readFile(f);
	
	sort(v.begin(), v.end());
	
	for(i = 0; i < v.size(); i++)
		for(j = 0; j != v[i].size(); j++)
			r += ((int)v[i][j] -  64) * (i + 1);
	
	return r;
}

int main() {
	cout << "result = " << calcScore("names.txt") << endl;

	return 0;
}
