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

/*
	Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference
	are pentagonal and D = |Pk − Pj| is minimised; what is the value of D?
*/

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

int getDifferencePentagonal() {
	long long v;
	set<long long>::iterator x, y;
	
	for(x = pentagonals.begin(); x != pentagonals.end(); x++) {
		for(y = pentagonals.begin(); y != x; y++) {
			v = (*x - *y >= 0) ? *x - *y : (*x - *y) * -1;
			
			if(isPentagonal(v) && isPentagonal(*x + *y))
				return v;
		}
	}
}

int main() {
	pentagonals = IamLupo::Pentagonal::generate(8000000);
	
	cout << "result = " << getDifferencePentagonal() << endl;
	
	return 0;
}