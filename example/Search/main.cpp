#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/pentagonal.h"

using namespace std;

static IamLupo::Primes primes;
static IamLupo::Pentagonals pentagonals;

bool isPentagonal(int v) {
	int i, x, t;
	
	t = 1;
	x = 1;
	
	while(t < v) {
		x += 3;
		t += x;
	}
	
	if(v == t)	
		return true;
	
	return false;
}

int main() {
	int i;
	
	/*
	vector<long long>::iterator it;
	primes = IamLupo::Prime::generate(1000000);
	
	cout << clock() << endl;
	it = find(primes.begin(), primes.end(), 988877);
	cout << clock() << endl;
	
	cout << clock() << endl;
	binary_search(primes.begin(), primes.end(), 988877);
	cout << clock() << endl;
	*/
	
	//Debug
	//for(i = 0; i < primes.size(); i++)
	//	cout << primes[i] << endl;
	
	unsigned int start, end;
	set<long long>::iterator it;
	
	pentagonals = IamLupo::Pentagonal::generate(10000);
	
	start = clock();
	it = find(pentagonals.begin(), pentagonals.end(), 988877);
	end = clock();
	cout << start << " > " << end << " = " << end - start << endl;
	
	start = clock();
	binary_search(pentagonals.begin(), pentagonals.end(), 988877);
	end = clock();
	cout << start << " > " << end << " = " << end - start << endl;
	
	start = clock();
	isPentagonal(988877);
	end = clock();
	cout << start << " > " << end << " = " << end - start << endl;
	
	return 0;
}
