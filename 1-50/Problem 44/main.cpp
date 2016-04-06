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

int getDifferencePentagonal() {
	long long v;
	vector<long long>::iterator x, y;
	
	for(x = pentagonals.begin(); x != pentagonals.end(); x++) {
		for(y = pentagonals.begin(); y != x; y++) {
			v = (*x - *y >= 0) ? *x - *y : (*x - *y) * -1;
			
			if(IamLupo::Pentagonal::is(v) && IamLupo::Pentagonal::is(*x + *y))
				return v;
		}
	}
}

int main() {
	pentagonals = IamLupo::Pentagonal::generate(8000000);
	
	cout << "result = " << getDifferencePentagonal() << endl;
	
	return 0;
}