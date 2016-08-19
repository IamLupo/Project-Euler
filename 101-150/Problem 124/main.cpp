#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	If rad(n) is sorted for 1 ≤ n ≤ 100000, find E(10000).
*/

typedef vector<vector<long long>> Matrix;

static IamLupo::Primes primes;

void draw(const Matrix &m) {
	int i, j;
	
	for(i = 1; i < m.size(); i++) {
		cout << "{";
		
		for(j = 0; j < m[i].size(); j++)
			cout << m[i][j] << ", ";
		
		cout << "}" << endl;
	}
}

int rad(int n) {
	int i, r;
	
	//Init
	r = 1;
	
	for(i = 0; i < primes.size(); i++) {
		if(n % primes[i] == 0) {
			n /= primes[i];
			
			//Save rest			
			r *= primes[i];
			
			//Remove the rest
			while(n % primes[i] == 0)
				n /= primes[i];
		}
		
		if(n == 1)
			return r;
	}
	
	return -1; // To less primes
}

int f(int l, int p) {
	int i, t;
	Matrix m(l + 1);
	
	//Init
	p -= 2;
	
	//Generate list
	for(i = 2; i <= l; i++)
		m[rad(i)].push_back(i);
	
	// Debug
	//draw(m);
	
	//Filter result
	for(i = 0; i < m.size(); i++) {
		if(m[i].size() > p)
			return m[i][p];
		
		p -= m[i].size();
	}
	
	return -1; // to high p
}

int main() {
	primes = IamLupo::Prime::generate(100000);
	
	cout << "Result = " << f(100000, 10000) << endl;

	return 0;
}
