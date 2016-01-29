#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
	How many different ways can £2 be made using any number of coins?
*/

//1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
static vector<int> options = { 1, 2, 5, 10, 20, 50, 100, 200 };

long long countChangeOptions(int r) {
	int i, j;
	vector<long long> a;
	
	//Init
	a.push_back(1);
	for(i = 1; i < r; i++)
		a.push_back(0);
	
	//Calc
	for(i = 0; i < options.size(); i++) {
		for(j = options[i]; j <= r; j++) {
			a[j] += a[j - options[i]];
		}
	}
	
	return a[r];
}

int main() {
	cout << "result = " << countChangeOptions(10000) << endl;
	
	return 0;
}