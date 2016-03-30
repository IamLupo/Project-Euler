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
	What is the maximum 16-digit string for a "magic" 5-gon ring?
*/

typedef vector<int> GonRing;
typedef vector<int> GonRingResults;

static vector<GonRingResults> grr_list;

/*
	Example:
		f({1,2,3,4,5,6}) = {2, 1, 3, 4, 3, 5, 6, 5, 1}
*/
GonRingResults convert(GonRing &gr) {
	int i;
	vector<int> r;
	
	for(i = 0; i < gr.size() - 2; i += 2) {
		r.push_back(gr[i + 1]);
		r.push_back(gr[i]);
		r.push_back(gr[i + 2]);
	}
	
	r.push_back(gr[i + 1]);
	r.push_back(gr[i]);
	r.push_back(gr[0]);
	
	return r;
}

/*
	Example:
		f({2, 1, 3, 4, 3, 5, 6, 5, 1}) = true, because 2 > 4 and 2 > 6
*/
bool check(GonRingResults &grr) {
	int i, j, v;
	bool f;
	
	v = grr[0];
	
	//Check other groups if it has higher
	for(i = 3; i < grr.size(); i += 3)
		if(v > grr[i])
			return false;
	
	return true;
}

void bruteforce(GonRing &gr, int s, int l, int m) {
	int i, v;
	
	//Max level reached
	if(l == m - 1) {
		GonRingResults grr;
		
		//Generate last value
		v = s - gr[0] - gr[l * 2];
		
		//Check if last value is in range and does not exist in the gonring yet
		if(v > 0 && v <= m * 2 && find(gr.begin(), gr.end(), v) == gr.end()) {
			gr.push_back(v);
			
			//Convert GonRing to GonRing Result
			grr = convert(gr);
			
			//Check if GonRing Result has the right structure
			if(check(grr))
				grr_list.push_back(grr);
		}
		
		return;
	}
	
	//Generate new GonRings
	for(i = 1; i <= m * 2; i++) {
		v = s - gr[l * 2] - i;
		
		//Check if the two values are in range and does not exist in the gonring yet
		if(	v > 0 && v <= m * 2 && i != v &&
			find(gr.begin(), gr.end(), i) == gr.end() &&
			find(gr.begin(), gr.end(), v) == gr.end()) {
			
			GonRing temp_gr;
			
			//Generate a new gonring
			temp_gr = gr;
			temp_gr.push_back(i);
			temp_gr.push_back(v);
			
			//bruteforce next level
			bruteforce(temp_gr, s, l + 1, m);
		}
	}
}

long long getMaximumDigits(int m, int d) {
	int i, j, l, s;
	long long v, r;
	GonRing gr;
	
	//Init
	r = 0;
	
	//Get all possible Gon Rings
	for(i = 1; i <= (m * 6) - 3; i++) {
		for(j = 1; j <= m * 2; j++) {
			gr = {j};
			bruteforce(gr, i, 0, m);
		}
	}
	
	//Find the one with {d} digit and highest value
	for(i = 0; i < grr_list.size(); i++) {
		v = 0;
		l = 0;
		s = grr_list[i].size() - 1;
		
		//Convert GonRing Result to Integer
		for(j = 0; j < s + 1; j++) {
			v += grr_list[i][s - j] * pow(10, l);
			
			if(grr_list[i][s - j] > 9)
				l += 2;
			else
				l++;
		}
		
		if(v < pow(10, d) && v > r)
			r = v;
	}
	
	return r;
}

int main() {
	//Example
	//cout << "result = " << getMaximumDigits(3, 9) << endl;
	
	cout << "result = " << getMaximumDigits(5, 16) << endl;
	
	return 0;
}