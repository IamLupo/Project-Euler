#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/pentagonal.h"

using namespace std;

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
	unsigned int start, end;
	IamLupo::Pentagonals::iterator it;
	
	pentagonals = IamLupo::Pentagonal::generate(1000000000);
	
	cout << pentagonals[pentagonals.size() - 1] << endl;
	
	start = clock();
	it = find(pentagonals.begin(), pentagonals.end(), 999995690);
	end = clock();
	cout << "find = " << end - start << " ticks" << endl;
	
	start = clock();
	binary_search(pentagonals.begin(), pentagonals.end(), 999995690);
	end = clock();
	cout << "binary_search = " << end - start << " ticks" << endl;
	
	start = clock();
	isPentagonal(999995690);
	end = clock();
	cout << "isPentagonal = " << end - start << " ticks" << endl;
	
	start = clock();
	IamLupo::Pentagonal::is(999995690);
	end = clock();
	cout << "IamLupo::Pentagonal::is = " << end - start << " ticks" << endl;
	
	return 0;
}
