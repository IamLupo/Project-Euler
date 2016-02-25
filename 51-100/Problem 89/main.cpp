#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/roman.h"

using namespace std;

/*
	Find the number of characters saved by writing each of these in their minimal form.
*/

/*
static vector<string> roman_symbols = {
	"I",   "II",  "III",  "IV",  "V",   "VI",   "VII",  "VIII",  "IX",  "X",
	"XI",  "XII", "XIII", "XIV", "XV",  "XVI",  "XVII", "XVIII", "XIX", "XX", 
	"XXX", "XL",  "L",    "LX",  "LXX", "LXXX", "XC",   "C",
	"CC",  "CCC", "CD",   "D",   "DC",  "DCC",  "DCCC", "CM",    "M"
};

static vector<int> roman_value = {
	1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	30, 40, 50, 60, 70, 80, 90, 100,
	200, 300, 400, 500, 600, 700, 800, 900, 1000
};

int toRoman(const string &s) {
	int i, v;
	
	v = 0;
			
	for(i = 0; i < s.size(); i++) {
		switch(s[i]) {
			case 'I':
				if(s[i + 1] == 'X') {
					v += 9;
					i++;
				}
				else if(s[i + 1] == 'V') {
					v += 4;
					i++;
				}
				else
					v += 1;
			break;
			case 'V':	v += 5;		break;
			case 'X':
				if(s[i + 1] == 'L') {
					v += 40;
					i++;
				}
				else if(s[i + 1] == 'C') {
					v += 90;
					i++;
				}
				else
					v += 10;
			break;
			case 'L':
					v += 50;
			break;
			case 'C':
				if(s[i + 1] == 'D') {
					v += 400;
					i++;
				}
				else if(s[i + 1] == 'M') {
					v += 900;
					i++;
				}
				else
					v += 100;
			break;
			case 'D':	v += 500;	break;
			case 'M':	v += 1000;	break;
		}
	}
	
	return v;
}

string toRoman(int n) {
	int i, v;
	string r;
	
	v = n;
	
	for(i = roman_value.size() - 1; i >= 0; i--) {
		if(v >= roman_value[i]) {
			v -= roman_value[i];
			r.append(roman_symbols[i]);
			i++;
		}
	}
	
	return r;
}
*/

vector<string> readFile(const string &f) {
	int i;
	string l;
	vector<string> r;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, l);
			r.push_back(l);
		}
	}
	
	file.close();
	
	return r;
}

int countMinimalRomanCharters(const string &f) {
	int i, r, n;
	string s;
	vector<string> v;
	
	r = 0;
	v = readFile(f);
	
	for(i = 0; i < v.size(); i++) {
		s = IamLupo::Roman::to(IamLupo::Roman::to(v[i]));
		r += v[i].size() - s.size();
	}
	
	return r;
}

int main() {
	cout << "result = " << countMinimalRomanCharters("roman.txt") << endl;
	
	return 0;
}
