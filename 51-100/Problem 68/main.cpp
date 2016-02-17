#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	it is possible to form 16- and 17-digit strings.
	What is the maximum 16-digit string for a "magic" 5-gon ring?
*/

typedef vector<int> GonRing;
typedef vector<int> GonRingResults;

static vector<GonRingResults> grr_list;

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
	GonRing temp_gr;
	GonRingResults grr;
	vector<int>::iterator a, b;
	
	if(l == m - 1) {
		v = s - gr[0] - gr[l * 2];
		a = find(gr.begin(), gr.end(), v);
		
		if(v > 0 && v <= m * 2 && a == gr.end()) {
			gr.push_back(v);
			grr = convert(gr);
			
			if(check(grr)) {
				grr_list.push_back(grr);
			}
		}
		
		return;
	}
	
	for(i = 1; i <= m * 2; i++) {
		v = s - gr[l * 2] - i;
		a = find(gr.begin(), gr.end(), i);
		b = find(gr.begin(), gr.end(), v);
		
		if(v > 0 && v <= m * 2 && i != v && a == gr.end() && b == gr.end()) {
			temp_gr = gr;
			temp_gr.push_back(i);
			temp_gr.push_back(v);
			
			bruteforce(temp_gr, s, l + 1, m);
		}
	}
}

long long getMaximumDigits(int m, int d) {
	int i, j, l, s;
	long long v, h;
	GonRing gr;
	
	h = 0;
	
	//Get all possible Gon Rings
	for(i = 1; i <= (m * 6) - 3; i++) {
		for(j = 1; j <= m * 2; j++) {
			gr = {j};
			bruteforce(gr, i, 0, m);
		}
	}
	
	//Find the one with 16 digit and highest value
	for(i = 0; i < grr_list.size(); i++) {
		v = 0;
		l = 0;
		s = grr_list[i].size() - 1;
		
		for(j = 0; j < s + 1; j++) {
			v += grr_list[i][s - j] * pow(10, l);
			
			if(grr_list[i][s - j] > 9)
				l += 2;
			else
				l++;
		}
		
		if(v < pow(10, d) && v > h)
			h = v;
	}
	
	return h;
}

int main() {
	cout << "result = " << getMaximumDigits(5, 16) << endl;
	
	return 0;
}