#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/divider.h"

using namespace std;

/*
	Evaluate the sum of all the amicable numbers under 10000.
*/

int sumAmicable(int x) {
	int i, r;
	std::vector<int> v;
	
	//Init
	r = 0;
	v = IamLupo::Divider::generate_sum(x);
	
	for(i = 1; i < v.size(); i++)
		if(v[i] <= x && v[i] != i && v[v[i]] == i)
			r += i;
	
	return r;
}

int main() {
	cout << "result = " << sumAmicable(10000) << endl;
	
	return 0;
}