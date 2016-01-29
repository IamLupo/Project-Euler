#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	For which value of p ≤ 1000, is the number of solutions maximised?
*/

bool isInList(vector<vector<int>> &l, int v) {
	int i;
	vector<int>::iterator it;
	
	for(i = 0; i < l.size(); i++) {
		it = l[i].end();
		
		if(find(l[i].begin(), it, v) != it)
			return true;
	}
	
	return false;
}

int getAnglesTriangle(int p) {
	int i, j, k;
	vector<int> v;
	vector<vector<int>> l;
	
	for(i = 1; i < p; i++) {
		for(j = 1; i + j < p && !isInList(l, i); j++) {
			k = p - i - j;
			if(k > 0 && i * i + j * j == k * k &&
				!isInList(l, j) && !isInList(l, k)) {
					v.clear();
					v.push_back(i);
					v.push_back(j);
					v.push_back(k);
					l.push_back(v);
			}
		}
	}
	
	return l.size();
}

int getMaxAnglesTriangle(int p) {
	int i, t, r, s;
	
	r = 0;
	
	for(i = 1; i <= p; i++) {
		t = getAnglesTriangle(i);
		if(t > r) {
			r = t;
			s = i;
		}
	}
	
	return s;
}

int main() {
	cout << "result = " << getMaxAnglesTriangle(1000) << endl;
	
	return 0;
}