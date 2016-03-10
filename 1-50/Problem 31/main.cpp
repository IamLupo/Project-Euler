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
	How many different ways can £2 be made using any number of coins?
*/

long long ways(const vector<int> &o, int n) {
	int i, j;
	vector<long long> a(n + 1, 0);
	
	//Init
	a[0] = 1;
	
	//Calc
	for(i = 0; i < o.size(); i++)
		for(j = o[i]; j <= n; j++)
			a[j] += a[j - o[i]];
	
	return a[n];
}

int main() {
	cout << "result = " << ways({1, 2, 5, 10, 20, 50, 100, 200}, 200) << endl;
	
	return 0;
}