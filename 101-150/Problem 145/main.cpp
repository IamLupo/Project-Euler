#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/vector.h"
#include "IamLupo/number.h"

using namespace std;

/*
	How many reversible numbers are there below one-billion (10^9)?
*/

/*
	z = f(x) - f(x-1)
	
	Data:
		x		f(x)		z
		1		0			0
		2		20			20
		3		120			100
		4		720			600
		5		720			0
		6		18720		18000
		7		68720		50000
		8		608720		540000
		9		608720		0
	
	Conclusion A:
		Bruteforcing f(9) took to long. Because i saw it has the same answer at f(4) and f(5)
		I expected this could also happend with f(8) and f(9).
		
	Conclusion B:
		Between every 4e position there is z = 0. 
*/

bool check(long long n) {
	int i;
	vector<int> v;
	
	//Init
	v = IamLupo::Vector::to(n);
	
	for(i = 0; i < v.size(); i++)
		if(v[i] % 2 == 0)
			return false;
	
	return true;
}

int f2(int l) {
	int i, n, r;
	vector<int> v;
	
	//Init
	r = 0;
	
	for(i = 1; i < pow(10, l); i++) {
		v = IamLupo::Vector::to(i);
		n = IamLupo::Number::to(v);
		
		if(i <= n && check(i + n)) {
			r += 2;
			
			cout << i << " + " << n << " = " << i + n << endl;
		}
	}
	
	return r;
}

int f(int l) {
	int i, r;
	
	//Init
	r = 0;
	
	for(i = 0; i < l - 1; i++) {
		switch(i % 4) {
			case 0:
			case 2:
				r += 20 * pow(30, (i / 2));
			break;
			case 1:
				r += 100 * pow(500, (i / 4));
			break;
			case 3:
			break;
		}
	}
	
	return r;
}

int main() {
	cout << "Result = " << f(9) << endl;
	
	return 0;
}
