#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

long long pentagonalNumber(long long n) {
	return (3 * n * n - n) / 2;
}

int powom1(int k) {
	if(k % 4 == 1 || k % 4 == 2)
		return 1;
	else
		return -1;
}

int main() {
	int i, j, t;
	int total = 0;
	vector<long long> penta, p;

	//Init
	p.push_back(1);
	
	//Generate penta
	for(i = -100000; i <= 100000; i++)
		penta.push_back(pentagonalNumber(i));
	
	sort(penta.begin(), penta.end());
	
	
	for(j = 1; j <= 100000; j++) {
		t = 0;
		
		for(i = 1; penta[i] <= j; i++) {
			t += powom1(i) * p[j - penta[i]];
			t %= 1000000;
		}

		p.push_back(t);

		//cout << t << endl;
		
		if(t == 0) {
			cout << j << endl;
			break;
		}
	}
	
	return 0;
}
