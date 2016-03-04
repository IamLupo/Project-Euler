#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/string.h"
#include "IamLupo/vector.h"

using namespace std;

/*
	What is the largest square number formed by any member of such a pair?
*/

typedef vector<string> Pair;

vector<string> readFile(const string &f) {
	int i;
	string l, v;
	vector<string> t, r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			//Read line
			getline(file, l);
			t = IamLupo::String::explode(l, ',');
			
			for(i = 0; i < t.size(); i++) {
				//filter word
				v = t[i].substr(1, t[i].size() - 2);
				
				//filter Palindrome words
				if(!IamLupo::String::isPalindrome(v))
					r.push_back(v);
			}
		}
	}
	
	file.close();
	
	return r;
}

vector<Pair> getWordPairs(const vector<string> &w) {
	int i, j;
	vector<Pair> r;
	
	for(i = 0; i < w.size(); i++)
		for(j = i + 1; j < w.size(); j++)
			if(w[i].size() == w[j].size() && IamLupo::String::common(w[i], w[j]))
				r.push_back({w[i], w[j]});
	
	return r;
}

bool valid(const vector<int> &v, const string &s, string &c) {
	int i, j;
	
	//Init
	c = "----------";
		
	for(i = 0; i < v.size(); i++) {
		if(c[v[i]] == '-')
			c[v[i]] = s[i];
		else if(c[v[i]] != s[i])
			return false;
	}
	
	for(i = 0; i < c.size(); i++)
		for(j = i + 1; j < c.size(); j++)
			if(c[i] == c[j] && c[i] != '-')
				return false;
	
	return true;
}

long long toInteger(const string &s, const string &c) {
	int i, j;
	long long r;
	
	r = 0;
	
	for(i = 0; i < s.size(); i++) {
		r *= 10;
		
		for(j = 0; j < c.size(); j++)
			if(s[i] == c[j])
				r += j;
	}
	
	return r;
}

int findLargestSquareNumber(const string &f) {
	int i, j, r;
	long long v1, v2, t;
	string config;
	vector<int> x;
	vector<string> w;
	vector<Pair> p;
	
	//Init
	r = 0;
	w = readFile(f);
	
	//Get words with common letters
	p = getWordPairs(w);
	
	//Generate a valid square number
	for(i = 0; i < p.size(); i++) {
		for(j = 1; j < 150; j++) {
			v1 = (long long)j * (long long)j;
			x = IamLupo::Vector::to(v1);
			
			if(p[i][0].size() == x.size() && valid(x, p[i][0], config)) {
				v2 = toInteger(p[i][1], config);
				t = sqrt(v2);
				
				if(t * t == v2 && v2 >= pow(10, x.size() - 1)) {
					if(v1 > r || v2 > r)
						r = (v1 > v2) ? v1 : v2;
					
					//Debug
					/*
					cout << "-------------------" << endl;
					cout << p[i][0] << "	" << v1 << endl;
					cout << p[i][1] << "	" << v2 << endl;
					*/
				}
				
			}	
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << findLargestSquareNumber("words.txt") << endl;
	
	return 0;
}
