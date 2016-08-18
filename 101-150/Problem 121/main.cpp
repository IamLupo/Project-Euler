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
	Find the maximum prize fund that should be allocated to a 
	single game in which fifteen turns are played.
*/

/*
	Data:
		1
		1, 1
		1, 3, 2
		1, 6, 11, 6
		1, 10, 35, 50, 24
		1, 15, 85, 225, 274, 120
		1, 21, 175, 735, 1624, 1764, 720
		1, 28, 322, 1960, 6769, 13132, 13068, 5040
		....
*/

vector<long long> next(const vector<long long> &v, int l) {
	int i;
	vector<long long> v2;
	
	//Init
	v2.push_back(1);
	
	for(i = 0; i < v.size(); i++) {
		if(i + 1 < v.size())
			v2.push_back(v[i] * l + v[i + 1]);
		else
			v2.push_back(v[i] * l);
	}
	
	return v2;
}

long long f(int n) {
	int i;
	long long w, l;
	vector<long long> v;
	
	//Init
	v = {};
	
	for(i = 0; i <= n; i++)
		v = next(v, i);
	
	//total wins
	w = accumulate(v.begin(), v.begin() + (n / 2) + 1, (long long)0);
	
	//total loses
	l = accumulate(v.begin(), v.end(), (long long)0);
	
	return l / w;
}

int main() {
	cout << "Result = " << f(15) << endl;
	
	return 0;
}
