#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/divider.h"

/*
	Find the sum of all the positive integers which cannot be written
	as the sum of two abundant numbers.
*/

/*
	Data:
		sum of the proper divisors:
		28	>	1 + 2 + 4 + 7 + 14 = 28
		
		abundant number:
		12	>	1 + 2 + 3 + 4 + 6 = 16
*/

using namespace std;

long long sumNoneAbundant() {
	int i, j;
	long long r;
	vector<int> a;
	vector<bool> v(28124, false);
	
	//Init
	r = 0;
	a = IamLupo::Divider::getAbundant(28123);
	
	//Generate all value that can be generated with two Abundant numbers
	for(i = 0; i < a.size(); i++)
		for(j = 0; j < a.size() && a[i] + a[j] <= 28123; j++)
			if(!v[a[i] + a[j]])
				v[a[i] + a[j]] = true;

	//Add all numbers that can not be generated
	for(i = 0; i < v.size(); i++)
		if(!v[i])
			r += i;
	
	return r;
}

int main() {
	cout << "result = " << sumNoneAbundant() << endl;

	return 0;
}