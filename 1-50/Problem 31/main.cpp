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

long long countChangeOptions(int n) {
	int i, j;
	vector<long long> a(n + 1, 0);
	
	//Init
	a[0] = 1;
	
	//Calc
	for(i = 0; i < options.size(); i++) {
		for(j = options[i]; j <= n; j++) {
			a[j] += a[j - options[i]];
		}
	}
	
	return a[n];
}

int main() {
	cout << "result = " << countChangeOptions(200) << endl;
	
	return 0;
}