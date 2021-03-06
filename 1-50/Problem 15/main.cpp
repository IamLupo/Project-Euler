#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"

using namespace std;

/*
	How many such routes are there through a 20×20 grid?
*/

/*
	f(1) = 2
				2
			1		1
				1
				
				
	f(2) = 6
				6
			3		3
		1		2		1
			1		1
				1
	
	f(3) = 20
				20
			10		10
		4		6		4
	1		3		3		1
		1		2		1
			1		1
				1
*/

long long countRoutes(int l) {
	int i;
	vector<long long> r;
	
	r = {1, 1};
	
	for(i = 1; i < l; i++) {
		r = IamLupo::Vector::add(r);
		r.push_back(1);
		r.insert(r.begin(), 1);
	}
	
	for(i = 0; i < l; i++)
		r = IamLupo::Vector::add(r);
	
	return r[0];
}

int main() {
	cout << "result = " << countRoutes(20) << endl;
	
	return 0;
}
