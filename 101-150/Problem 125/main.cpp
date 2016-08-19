#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/string.h"

using namespace std;

/*
	Find the sum of all the numbers less than 10^8 that are both palindromic
	and can be written as the sum of consecutive squares.
*/

long long f(int p) {
	int i, j, m, v;
	set<int> r;
	
	//Init
	m = pow(10, p);
	
	for(i = 1; (i * i) + ((i + 1) * (i + 1)) <= m; i++) {
		v = i * i;
		for(j = i + 1; v + j * j <= m; j++) {
			v += j * j;
			
			if(IamLupo::String::isPalindrome(to_string(v)))
				r.insert(v);
		}
	}
	
	return accumulate(r.begin(), r.end(), (long long)0);
}

int main() {
	cout << "Result = " << f(8) << endl;
	
	return 0;
}
