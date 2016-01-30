#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

using namespace std;

/*
	Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
	contain the same digits.
*/

vector<int> toVector(int v) {
	vector<int> r;
	
	while(v != 0) {
		r.push_back(v % 10);
		v /= 10;
	}
	
	return r;
}

bool isSameVector(vector<int> a, vector<int> b) {
	int i;
	
	if(a.size() != b.size())
		return false;
	
	for(i = 0; i < a.size(); i++) {
		if(a[i] != b[i])
			return false;
	}
	
	return true;
}

int findSmallest(int l) {
	int i, j, c;
	vector<int> v, t;
	bool f;
	
	c = pow(10, l) / 6;
	
	for(i = pow(10, l - 1); i < c; i++) {
		v = toVector(i);
		f = true;
		
		sort(v.begin(), v.end());
		
		for(j = 2; j <= l; j++) {
			t = toVector(j * i);
			sort(t.begin(), t.end());
			
			if(!isSameVector(v, t))
				f = false;
		}
		
		if(f)
			return i;
	}
	
	return -1;
}

int main() {
	cout << "result = " << findSmallest(6) << endl;
	
	return 0;
}