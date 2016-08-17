#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	How many different ways can the black tiles in a row measuring
	fifty units in length be replaced if colours cannot be mixed
	and at least one coloured tile must be used?
*/

/* Slow Recursive */
long long count(int v, int len) {
	int i;
	long long r;
	
	//Init
	r = 0;
	
	r += len - v + 1;
	
	for(i = 0; i <= len - (2 * v); i++)
		r += count(v, len - v - i);
	
	return r;
}

long long f2(int n) {
	int i;
	long long r;
	
	//Init
	r = 0;
	
	for(i = 2; i <= 4; i++)
		r += count(i, n);
	
	return r; // Unknown
}

/* Fast */
/*
	Red:
		Sum C(n-k,k+1), k=0..floor(n)
	
	Green:
		Sum C(n-2k,k+1), k=0..floor(n/2)
	
	Blue:
		Sum C(n-3k,k+1), k=0..floor(n/4)
	
	Reference:
		http://oeis.org/A098578
		http://oeis.org/A077868
		http://oeis.org/A000071
*/
long long f(int n) {
	int k;
	long long r;
	
	//Init
	r = 0;
	n--;
	
	for(k = 0; k <= n; k++) {
		//Red
		r += IamLupo::Math::binomial_coefficient(n - k, k + 1);
		
		//Green
		if(k <= (n - 1) / 2)
			r += IamLupo::Math::binomial_coefficient(n - 1 - (2 * k), k + 1);
		
		//Blue
		if(k <= (n - 2) / 4)
			r += IamLupo::Math::binomial_coefficient(n - 2 - (3 * k), k + 1);
	}
	
	return r;
}

int main() {
	cout << "Result = " << f(50) << endl;
	
	return 0;
}
