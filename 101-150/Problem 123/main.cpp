#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	Find the least value of n for which the remainder first exceeds 10^10.
*/

static IamLupo::Primes primes;

/*
	Generated eureqa formula to skip checking primes and
	start at nearly close to solution the results
	
	Tested for result till 10^15 and lower
*/
int start(int x) {
	float a, b, c, d, e, r;
	
	/*
		y = 0.303232697920926*x^3 + 0.0919843851070339*x*exp(x) + 1.21794764462935e-5*x*exp(1.5228266443024*x) - 6.66159037803082e-8*exp(2*x)
	*/
	a = 0.303232697920926;
	b = 0.0919843851070339;
	c = 1.21794764462935e-5;
	d = 1.5228266443024;
	e = 6.66159037803082e-8;
	
	//Calc
	r = (a*pow(x, 3) + b*x*exp(x)) + (c*x*exp(d*x)) - (e*exp(2*x));
	
	/*
		some results where to high. subtracted 22 to
		always have a lower start potion then the origal answer
	*/
	r -= 22;
	
	return (r < 0 ? 0 : r);
}

long long f(int p) {
	int i;
	
	// Loop even prime index id's
	for(i = start(p); i < primes.size(); i += 2) { 
		//Debug
		//cout << i << "	" << primes[i] * c << endl;
		
		// Check results
		if(primes[i] * ((i + 1) * 2) > pow(10, p))
			return i + 1;
	}
	
	return -1; // Generate more primes pls :'(
}

int main() {
	primes = IamLupo::Prime::generate(240000);
	
	cout << "Result = " << f(10) << endl;
	
	return 0;
}
