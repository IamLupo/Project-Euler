#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>

using namespace std;

/*
	What is the largest n-digit pandigital prime that exists?
*/

const vector<string> explode(const string& s, const char& c) {
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
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

int getWordNumber(string v) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		if(v[i] != '"')
			r += (int)v[i] - 64;
	
	return r;
}

int countTriangleWords(string s) {
	int i, r;
	ifstream input(s);
	string line;
	
	getline(input, line);
	vector<string> v{explode(line, ',')};
	
	for(i = 0; i < v.size(); i++)
		if(isTriangle(getWordNumber(v[i])))
			r++;
	
	return r;
}

int main() {
	cout << "result = " << countTriangleWords("words.txt") << endl;
	
	return 0;
}